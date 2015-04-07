#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#define ERR(x) {perror(x);exit(errno);}


int main()
{
	int server_fd,client_fd,cpid;
	socklen_t client_len;
	char cmd[100] = "Welcome to Johnny's server!\n";
	struct sockaddr_in server_sock;
	struct sockaddr_in client_sock;
	
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(8080);
	
	//清理socket
	close(server_fd);	
	close(client_fd);

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
    

Listen:
    printf("Listening...\n");
    do{
        client_fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);  //等待客户端连接
    }while(client_fd == -1);
    
    
    cpid = fork();  //开辟子进程与客户端通信
    if(cpid == -1){
        ERR("fork");
    }
    else if(cpid == 0){
        while(strncmp(cmd,"quit",4) != 0){
            if(send(client_fd,cmd,sizeof(cmd),0) == -1){
                ERR("send cmd");
            }
            while(recv(client_fd,cmd,sizeof(cmd),0) == -1);
        }
        close(client_fd);
        printf("Client quit.\n");
        return 0;
    }
    else{
        close(client_fd);
        printf("client connected\n");
        goto Listen;    //父进程关闭client_fd，继续listen
    }
	
	return 0;
}


