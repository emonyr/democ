#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>

#include "include/connection.h"
#include "include/debug.h"

int creat_server_fd(const char port)
{
	int ret;

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


	ret = getaddrinfo(NULL,port,&hints,&result);
	if(ret != 0)
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
		//监听server_fd
		if(listen(server_fd,MAXCONNECT) == -1)
			ERR("listen");
		printf("Server standby.\n");
	}
		
	return 0;
}

void wait_for_connect(int fd,sockaddr_in *addr,socklen_t *addrlen)
{
	printf("Waiting for connection...\n");
	do{
		fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);
	}while(fd == -1)

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

int handle_request(int fd)
{
	int ret;
	
	ret = wait_for_input(client_fd,30);
	if(ret == 1)
		recv(client_fd,cmd,BUFSIZE,0);
	close(client_fd);
}













