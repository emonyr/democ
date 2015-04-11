#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <signal.h>
#include <dirent.h>
#define ERR(x) {perror(x);exit(errno);}

int sockfd;

void sig_exit_handler(int signum)
{
    if(signum == SIGINT || signum == SIGTERM){
        if(send(sockfd,"quit",5,0) == -1){
            ERR("send quit");
        }
    }
    exit(1);
}

int main(int argc,char **argv)
{
	if(argc != 2){
		printf("Usage: %s + <hostname>\n",argv[0]);exit(1);
	}

	char cmd[1024];
	struct sockaddr_in remote_sock;
	struct hostent *myhost;
	
	myhost = gethostbyname(argv[1]);
	if(myhost == NULL){
		ERR("gethostbyname");
	}
	printf("%s\n",myhost->h_addr);
	
	remote_sock.sin_family = AF_INET;
	remote_sock.sin_port = htons(8080);
	inet_aton(myhost->h_addr,(struct in_addr *)&remote_sock.sin_addr);
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1){
		ERR("sockfd");
	}
	if(connect(sockfd,(struct sockaddr *)&remote_sock,sizeof(remote_sock)) == -1){
		ERR("connect");
	}
    
    if(signal(SIGINT,sig_exit_handler) == SIG_ERR)
        ERR("signal SIGINT");
    if(signal(SIGTERM,sig_exit_handler) == SIG_ERR)
        ERR("signal SIGTERM");
    
	while(strncmp(cmd,"quit",4) != 0){
		if(recv(sockfd,cmd,1024,0) == -1){
			ERR("recv");
		}
		printf(">%s\n",cmd);
		fgets(cmd,1024,stdin);
		if(send(sockfd,cmd,1024,0) == -1){
			ERR("send cmd");
		}
	}
	close(sockfd);
	
	return 0;
}
