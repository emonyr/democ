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
#include <fcntl.h>
#define ERR(x) {send(sockfd,"quit",5,0);perror(x);exit(errno);}
#define BUFSIZE 128

int sockfd,nbyte;
struct sockaddr_in remote_sock;
char cmd[BUFSIZE];
char arg[BUFSIZE];
char buf[BUFSIZE];

char *getarg(const char *s) //此函数返回s中的第二段非空字符串
{
    int i=0,j=0;
    
    while(s[i] != ' ')
        i++;
    while(s[i] == ' ')
        i++;
    
    memset(arg,0,sizeof(arg));
    while(s[i] != '\n')
        arg[j++] = s[i++];
    
    if(j == 0){
        printf("getarg failed: void arg\n");exit(1);
    }
    
    return arg;
}

int cmd_help()
{
    if(recv(sockfd,buf,BUFSIZE,0) == -1)
        ERR("recv");
    printf("%s\n",buf);
    return 0;
}

int cmd_list()
{
	while((nbyte = recv(sockfd,buf,BUFSIZE,0)) > 0)
		printf("%s\n",buf);

    return 0;
}

int cmd_get()
{
	int content,sval;
	getarg(cmd);
	
	umask(0);
	if((content = open(arg,O_WRONLY|O_CREAT|O_TRUNC,0666)) < 0)
		ERR("open");
    
	while(nbyte = recv(sockfd,buf,BUFSIZE,0) > 0){
		if(strcmp(buf,"file doesn't exist.\n") == 0){
			printf("file doesn't exist.\n");
			close(content);
			unlink(arg);
			return -1;
		}
		write(content,buf,nbyte);
	}
	
	umask(sval);
	close(content);
	printf("file downloaded\n");
	
    return 0;
}

int cmd_put()
{
	int content;
    getarg(cmd);
	
    recv(sockfd,buf,BUFSIZE,0);
	printf("%s",buf);
    if(strcmp(buf,"failed to create file on server.\n") == 0)
        return -1;
    
	if((content = open(arg,O_RDONLY)) < 0)
		ERR("open");
	while((nbyte = read(content,buf,BUFSIZE)) > 0){
		if(send(sockfd,buf,nbyte,0) == -1)
        	perror("send file");
	}
	printf("file sent.\n");
    close(content);
	
    return 0;
}

int dispatch() //根据cmd分派任务
{
	memset(buf,0,sizeof(buf));
    if(strncmp(cmd,"help",4) == 0)
        cmd_help();
    else if(strncmp(cmd,"list",4) == 0)
        cmd_list();
    else if(strncmp(cmd,"get",3) == 0)
        cmd_get();
    else if(strncmp(cmd,"put",3) == 0)
        cmd_put();
    else{
		recv(sockfd,buf,BUFSIZE,0);
		printf("%s\n",buf);
    }
	memset(cmd,0,BUFSIZE);
    return 0;
}

void sig_exit_handler(int signum)   //如果程序异常终止，则通知server
{
    if(signum == SIGINT || signum == SIGTERM){
        if(send(sockfd,"quit",4,0) == -1)
            ERR("send quit");
    }
    exit(1);
}


int main(int argc,char **argv)
{
	if(argc != 2){
		printf("Usage: %s + <hostname>\n",argv[0]);exit(1);
	}

	struct hostent *myhost;
	if((myhost = gethostbyname(argv[1])) == NULL)
		ERR("gethostbyname");
	
	remote_sock.sin_family = AF_INET;
	remote_sock.sin_port = htons(8080);
	inet_aton(myhost->h_addr,(struct in_addr *)&remote_sock.sin_addr);
	
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
		ERR("sockfd");
	if(connect(sockfd,(struct sockaddr *)&remote_sock,sizeof(remote_sock)) == -1)
		ERR("connect");
	
    if(signal(SIGINT,sig_exit_handler) == SIG_ERR)
        ERR("signal SIGINT");
    if(signal(SIGTERM,sig_exit_handler) == SIG_ERR)
        ERR("signal SIGTERM");
    
	while(strncmp(cmd,"quit",4) != 0){
        dispatch();
        printf("\n>");
		fgets(cmd,BUFSIZE,stdin);
		send(sockfd,cmd,BUFSIZE,0);
	}
	close(sockfd);
	
	return 0;
}
