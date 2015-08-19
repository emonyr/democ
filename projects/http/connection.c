/*
 * connection.c 
 * 提供建立服务器连接的函数
 */

#include "global.h"

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

void wait_for_connect(int *fd,struct sockaddr_in *addr,socklen_t *addrlen)
{
	print_time();
	printf("Waiting for connection...\n");
	do{
		*fd = accept(server_fd,(struct sockaddr *)addr,addrlen);
	}while(*fd == -1);
}

void print_time(void)
{
	time_t timestamp;
	struct tm *showtime;

	time(&timestamp);
    showtime = localtime(&timestamp);
    printf("%02d:%02d:%02d ",showtime->tm_hour,showtime->tm_min,showtime->tm_sec);
}

int wait_for_input(int fd,int seconds)
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

void handle_request(int fd)
{
	int ret;
	
	ret = wait_for_input(fd,30);
	if(ret == 1)
		recv(fd,request_buf,BUFSIZE,0);
	dispatch(fd,request_buf);
	close(fd);
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










