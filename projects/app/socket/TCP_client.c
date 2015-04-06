#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#define ERR(x) {perror(x);exit(errno);}

int main(int argc,char **argv)
{
	int sockfd;
	char buf[100];
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
    
	while(strncmp(buf,"quit",4) != 0){
		if(recv(sockfd,buf,sizeof(buf),0) == -1){
			ERR("recv");
		}
		printf("From server: %s\n",buf);
		printf("Please input a command.\n");
		fgets(buf,100,stdin);
		if(send(sockfd,buf,sizeof(buf),0) == -1){
			ERR("send buf");
		}
	}
	close(sockfd);
	
	return 0;
}