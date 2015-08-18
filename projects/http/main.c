#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#include "include/connection.h"
#include "include/debug.h"


int main(int argc,const char *argv[])
{
	int client_fd = -1;
	struct sockaddr_in client_sock;
	socklen_t client_len;
	
	creat_server_fd(argv[1]);
	
wait:
	wait_for_connect(client_fd,(struct sockaddr *)&client_sock,&client_len);
	
	int cpid = fork();	//开辟子进程与客户端通信
	if(cpid == -1)
        ERR("fork");
    else if(cpid == 0){
		handle_request(client_fd);
	}
	else{
		close(client_fd);
		goto wait;
	}
	return 0;
}