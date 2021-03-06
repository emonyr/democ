#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
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

int wait_for_input(int fd,int time)
{

	fd_set readfds;
	struct timeval tv;

	//设置select fd_set
	FD_ZERO(&readfds);
	FD_SET(sockfd,&readfds);
	//等待50ms
	tv.tv_sec = time;
	tv.tv_usec = 500;

	return select(FD_SETSIZE,&readfds,NULL,NULL,&tv);

}

int cmd_help()
{
	while(wait_for_input(sockfd,0) == 1){
		nbyte = recv(sockfd,buf,BUFSIZE,0);
		printf("%s\n",buf);
	}
}

int cmd_list()
{
	while(wait_for_input(sockfd,0) == 1){
		nbyte = recv(sockfd,buf,BUFSIZE,0);
		printf("%s\n",buf);
	}
    return 0;
}

int cmd_get()
{
	int content,sval;
	getarg(cmd);
	
	umask(0);
	if((content = open(arg,O_WRONLY|O_CREAT|O_TRUNC,0666)) < 0)
		ERR("open");
	nbyte = recv(sockfd,buf,BUFSIZE,0);
	printf("%s\n",buf);

	while(wait_for_input(sockfd,0) == 1){
		nbyte = recv(sockfd,buf,BUFSIZE,0);
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
	send(sockfd,"ready to transfer",BUFSIZE,0);
    
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

	if (argc < 3) {
		fprintf(stderr, "Usage: %s host port msg...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	int ret;
	struct sockaddr_in remote_sock;
	struct addrinfo hints;
	struct addrinfo *result,*rp;

	
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;


	ret = getaddrinfo(argv[1],argv[2],&hints,&result);
	if(ret != 0)
		ERR("getaddrinfo");
	for(rp = result;rp != NULL;rp = result->ai_next){
		//获取socket
		if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1)
			continue;
		//连接到服务器
		if(connect(sockfd,rp->ai_addr,rp->ai_addrlen) == 0)
			break;
	}
	freeaddrinfo(result);

	
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
