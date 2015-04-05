#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#define ERR(x) {perror(x);exit(errno);}

int main()
{
	int server_fd,client_fd;
	socklen_t client_len;
	char welcome_msg[30] = "Welcome to Johnny's server!\n";
	char cmd[100] = "";
	struct sockaddr_in server_sock;
	struct sockaddr_in client_sock;
	
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(8080);
	
	server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_fd == -1){
		ERR("server_fd");
	}
	
	if(bind(server_fd,(struct sockaddr *)&server_sock,sizeof(server_sock)) == -1){
		ERR("bind");
	}
	
	if(listen(server_fd,50) == -1){
		ERR("listen");
	}
	printf("Listening...\n");
		
	client_fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);
	if(client_fd == -1){
		ERR("accept");
	}
	
	while(strncmp(cmd,"quit",4) != 0){
		if(strcmp(cmd,"") == 0){
			if(send(client_fd,welcome_msg,sizeof(welcome_msg),0) == -1){
				ERR("send");
			}
		}
		while(recv(client_fd,cmd,sizeof(cmd),0) == -1);
		if(send(client_fd,cmd,sizeof(cmd),0) == -1){
			ERR("send cmd");
		}
	}
	close(client_fd);
	close(server_fd);
	
	return 0;
}