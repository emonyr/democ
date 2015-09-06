/*
 * connection.c 
 * 提供建立服务器连接的函数
 */

#include "global.h"


const char month_tab[] ="Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec ";
const char day_tab[] = "Sun,Mon,Tue,Wed,Thu,Fri,Sat";

static int sock_opt = 1;
int server_fd = -1;

int creat_server_fd(const char *port)
{
	struct addrinfo hints;
	struct addrinfo *result,*rp;
	result = NULL;
	rp = NULL;

	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if(getaddrinfo(NULL,port,&hints,&result) != 0);
		ERR("getaddrinfo");
	for(rp = result;rp != NULL;rp = result->ai_next){
		//获取socket
		if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
			continue;
		//绑定server_fd
		if(bind(server_fd,rp->ai_addr,rp->ai_addrlen) == 0)
			break;
	}
	freeaddrinfo(result);
	if(server_fd == -1)
		ERR("socket");
	else{
		//设置server_fd为nonblock
		if(set_fd_flags(server_fd,O_NONBLOCK) == -1)
			ERR("fcntl:set nonblock");
		//禁止cgi写server_fd
		if (fcntl(server_fd, F_SETFD, 1) == -1)
			ERR("fcntl:set close-on-exec");
		//设置server_fd可复用
		if (setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&sock_opt,sizeof(sock_opt)) == -1) 
			ERR("setsockopt:set reuse");
		//监听server_fd
		if(listen(server_fd,BACKLOGSIZE) == -1)
			ERR("listen");
		printf("Server standby.\n");
	}
		
	return 0;
}

void wait_for_connect(int server_fd)
{
	int i,nfds,epoll_fd,client_fd;
	socklen_t client_len;
	struct sockaddr_in client_sock;
	struct epoll_event ev,events[MAX_EVENTS];
	
	epoll_fd = epoll_create(10);
	if(epoll_fd == -1)
		ERR("epoll_create");
	
	ev.events = EPOLLIN;
	ev.data.fd = server_fd;
	if (epoll_ctl(epoll_fd,EPOLL_CTL_ADD,server_fd,&ev) == -1)
		ERR("epoll_ctl: server_fd");
	
	while(1){
		//等待客户端连接
		printf("%s - Waiting for connection...\n",current_time());
		nfds = epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
		if(nfds == -1)
			ERR("epoll_wait");
		
		for(i = 0; i < nfds; ++i) {
			if(events[i].data.fd == server_fd) {
				client_fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);
				if(client_fd == -1)
					ERR("accept");
				//设置server_fd为nonblock
				if(set_fd_flags(client_fd,O_NONBLOCK) == -1)
					ERR("fcntl:set nonblock");
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = client_fd;
				if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,client_fd,&ev) == -1)
					ERR("epoll_ctl: client_fd");
			}else
				handle_fd(events[i].data.fd);
		}
	}
}

int handle_fd(int client_fd)
{
	struct request *req;
	req = (struct request *)malloc(sizeof(struct request));
	memset(req,0,sizeof(struct request));
	
	if(wait_to_read(client_fd,10) == 1){
		if(recv(client_fd,req->request_buf,BUFSIZE,0) < 0)
			ERR("recv");
	}
	
    //把request_buf读取到request结构体
	req->fd = client_fd;
	if(read_request(req) != 0){
		send_response(client_fd,NOT_FOUND);
		close(req->fd);
		free(req);
		ERR("read_request");
	}
	//把新request添加到pipe等待列表
	add_to_pipe(req);
	
	return 0;
}

void * handle_request(void *p)
{
	int i,nfds,epoll_fd;
	struct epoll_event ev,events[MAX_EVENTS];
	struct request *req;
	
	epoll_fd = epoll_create(10);
	if(epoll_fd == -1)
		ERR("epoll_create");
	
	ev.events = EPOLLIN;
	ev.data.fd = pipefd[0];
	if (epoll_ctl(epoll_fd,EPOLL_CTL_ADD,pipefd[0],&ev) == -1)
		ERR("epoll_ctl: pipefd[0]");
	
	while(1){
		nfds = epoll_wait(epoll_fd,events,MAX_EVENTS,-1);
		if(nfds == -1)
			ERR("epoll_wait");
		
		for(i = 0; i < nfds; ++i) {
			if(events[i].data.fd == pipefd[0])
			//获取互斥锁，读取pipe等待队列
			if(pthread_mutex_trylock(&lock) != 0);
				continue;
			read(pipefd[0],(void *)&req,sizeof(req));
			pthread_mutex_unlock(&lock);
			//分派request的具体操作
			if(req)
				dispatch(req);
		}
	}
	return NULL;
}

int add_to_pipe(struct request *req)
{
	pthread_mutex_lock(&lock);
	write(pipefd[1],(const void *)&req,sizeof(req));
	pthread_mutex_unlock(&lock);
	
	return 0;
}

char * current_time(void)
{
	time_t timestamp;
	struct tm *showtime;
	char day[4];
	char month[4];

	time(&timestamp);
    showtime = gmtime(&timestamp);
	strncpy(day,&day_tab[showtime->tm_wday * 4],3);
	strncpy(month,&month_tab[showtime->tm_mon * 4],3);
	day[3] = '\0';
	month[3] = '\0';
    sprintf(GMTtime,"%s,%02d %s %04d%02d:%02d:%02d GMT",day,showtime->tm_mday,month,showtime->tm_year+1900,showtime->tm_hour,showtime->tm_min,showtime->tm_sec);
	
	return GMTtime;
}

int wait_to_read(int fd,int seconds)
{
	int epoll_fd;
	struct epoll_event ev,events;
	
	epoll_fd = epoll_create(1);
	if(epoll_fd == -1)
		ERR("epoll_create");
	
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	if (epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&ev) == -1)
		ERR("epoll_ctl: fd");
	
	if(epoll_wait(epoll_fd,&events,1,seconds) == -1)
		ERR("epoll_wait");

	return events.data.fd;
}

int set_fd_flags(int fd,int new_flags)
{
    int flags;

    flags = fcntl(fd,F_GETFL);
    if (flags == -1)
        return -1;

    flags |= new_flags;
    flags = fcntl(fd,F_SETFL,flags);
    return flags;
}