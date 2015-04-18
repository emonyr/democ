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
#define ERR(x) {perror(x);exit(errno);}
#define CMDSIZE 512
#define BUFSIZE 128

int sockfd,nbyte;
char cmd[CMDSIZE];
char arg[CMDSIZE];
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
    if(recv(sockfd,buf,BUFSIZE,0) == -1){
        ERR("recv");
    }
    printf("%s\n",buf);
    return 0;
}

int cmd_list()
{
	int total;
	while(1){
		recv(sockfd,buf,BUFSIZE,0);
		if(strcmp(buf,"/EOF") == 0)
			break;
		printf("%s\n",buf);
	}

    return 0;
}

int cmd_get()
{
	int content,sval;
	getarg(cmd);
	
	umask(0);
	content = open(arg,O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(content < 0){
		ERR("open");
	}
    
	while(nbyte = recv(sockfd,buf,BUFSIZE,0)){
		if(strcmp(buf,"file doesn't exist.\n") == 0){
			printf("file doesn't exist.\n");
			return -1;
		}
		if(strcmp(buf,"/EOF") == 0){
			close(content);
			printf("file downloaded\n");
			return 0;
		}
		write(content,buf,nbyte);
	}
	
	umask(sval);
	close(content);
	
    return 0;
}

int cmd_put()
{
	int content;
    getarg(cmd);
    printf("%s\n",arg);
	
    recv(sockfd,buf,BUFSIZE,0);
    if(strcmp(buf,"failed to create file on server.\n") == 0){
        printf("failed to create file on server.\n");
        return -1;
    }
    
	content = open(arg,O_RDONLY);
	if(content < 0){
		ERR("open");
	}
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
	while(1){
		recv(sockfd,buf,BUFSIZE,0);
		if(strcmp(buf,"/EOF") == 0)
			break;
		printf("%s\n",buf);
	}
    }
    return 0;
}

void sig_exit_handler(int signum)   //如果程序异常终止，则通知server
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
        dispatch();
        printf("\n>");
		fgets(cmd,CMDSIZE,stdin);
		if(send(sockfd,cmd,CMDSIZE,0) == -1){
			ERR("send cmd");
		}
	}
	close(sockfd);
	
	return 0;
}
