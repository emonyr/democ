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

struct request * wait_for_connect(void)
{
	struct request *req;
	req = (struct request *)malloc(sizeof(struct request));
	memset(req,0,sizeof(struct request));
	
	int client_fd = -1;
	struct sockaddr_in client_sock;
	socklen_t client_len;
	
	printf("%s - Waiting for connection...\n",current_time());
	//等待客户端连接
	//设置select等待pipe列表被写入
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(server_fd,&readfds);
	select(FD_SETSIZE,&readfds,NULL,NULL,NULL);
	client_fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);
	if(wait_to_read(client_fd,5) == 1){
		if(recv(client_fd,req->request_buf,BUFSIZE,0) < 0)
			ERR("recv");
	}
	
	//把buf内容转换成小写字母
	if(all_to_lowercase(req->request_buf) == -1)
		ERR("all_to_lowercase");
	
    //把request_buf读取到request结构体
	req->fd = client_fd;
	if(read_request(req) != 0){
		send_response(client_fd,NOT_FOUND);
		close(req->fd);
		free(req);
		ERR("read_request");
	}
	
	return req;
}

void * handle_request(void *p)
{
	//设置select等待pipe列表被写入
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(pipefd[0],&readfds);
	select(FD_SETSIZE,&readfds,NULL,NULL,NULL);
	//尝试获取互斥锁，如失败则返回等待状态
	if(pthread_mutex_trylock(&lock) != 0)
		pthread_exit(NULL);
	struct request *req;
	read(pipefd[0],(void *)&req,sizeof(req));
	pthread_mutex_unlock(&lock);
	//分派request的具体操作
	if(req)
		dispatch(req);
	pthread_exit(NULL);
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

	fd_set readfds;
	struct timeval tv;

	//设置select fd_set
	FD_ZERO(&readfds);
	FD_SET(fd,&readfds);
	//至少等待1ms
	tv.tv_sec = seconds;
	tv.tv_usec = 1;

	return select(FD_SETSIZE,&readfds,NULL,NULL,&tv);
}

int wait_to_write(int fd,int seconds)
{

	fd_set writefds;
	struct timeval tv;

	//设置select fd_set
	FD_ZERO(&writefds);
	FD_SET(fd,&writefds);
	//至少等待1ms
	tv.tv_sec = seconds;
	tv.tv_usec = 1;

	return select(FD_SETSIZE,NULL,&writefds,NULL,&tv);
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