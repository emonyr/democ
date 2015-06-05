#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>
#define ERR(x) {perror(x);exit(errno);}
#define BUFSIZE 128
#define MAXCONNECT 10

int client_fd,*client_count,nbyte;
socklen_t client_len;
char cmd[BUFSIZE];
char arg[BUFSIZE];
char buf[BUFSIZE] = "\nWelcome to Johnny's server!\n\nPlease input a command.\n";


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
	FD_SET(client_fd,&readfds);
	//等待10分钟
	tv.tv_sec = time;
	tv.tv_usec = 500;

	return select(FD_SETSIZE,&readfds,NULL,NULL,&tv);

}


int cmd_help()
{
    if(send(client_fd,"Usage:\n\thelp\n\tlist\n\tget <file>\n\tput <file>\n\tquit\n",BUFSIZE,0) == -1)
        perror("send help");
    return 0;
}


int filter(const struct dirent *d)
{
	if((strcmp(d->d_name, ".") == 0) || (strcmp(d->d_name, "..") == 0) || (d->d_name == NULL)){
		return 0;
	}
	else
		return 1;
}


int cmd_list()
{
    int count,i=0;
    struct dirent **namelist;
    
    if((count = scandir(".",&namelist,filter,alphasort)) == -1)
        perror("scandir");
    for(i=0;i<count;i++){
	strcpy(buf,namelist[i]->d_name);
	if(send(client_fd,buf,BUFSIZE,0) == -1)
			ERR("send");
	free(namelist[i]);
    }
	free(namelist);

    return 0;
}


int cmd_get()
{
	int content,sval;
	getarg(cmd);
	
	umask(0);
	content = open(arg,O_RDONLY,0666);
	if(content < 0){
		send(client_fd,"file doesn't exist.\n",BUFSIZE,0);
        close(content);
        exit(1);
	}
	else
		send(client_fd,"ready to transfer",BUFSIZE,0);

	while((nbyte = read(content,buf,BUFSIZE)) != 0){
        	if(send(client_fd,buf,nbyte,0) == -1)
				perror("send file");
	}
	
	close(content);
	umask(sval);
    
    return 0;
}


int cmd_put()
{
	int content,sval;
    getarg(cmd);
	
    umask(0);
    content = open(arg,O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(content < 0){
        send(client_fd,"failed to create file on server.\n",BUFSIZE,0);
		unlink(arg);
        exit(1);
    }
	else
		send(client_fd,"Transferring file.\n",BUFSIZE,0);

	nbyte = recv(client_fd,buf,BUFSIZE,0);
	printf("%s\n",buf);

	while(wait_for_input(client_fd,0) == 1){
		nbyte = recv(client_fd,buf,BUFSIZE,0);
		write(content,buf,nbyte);
	}
    
	close(content);
	umask(sval);
	
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
	else if(strncmp(cmd,"quit",4) == 0)
        return 0;
    else if(send(client_fd,"Unknown command\nInput \"help\" for more information\n",BUFSIZE,0) == -1)
        ERR("send Unknown command");
	memset(cmd,0,sizeof(cmd));
    return 0;
}


void *set_client_count(const char *filename)    //实现连接计数器
{
    int shm_id,sval;
    void * ret;
    
    sval = umask(0);
    //从内核空间分配shm
    if ((shm_id = shmget(ftok(filename,'a'),sizeof(int),IPC_CREAT|0666)) == -1)
        ERR("shmget");
    //绑定shm到用户空间
    if ((ret = shmat(shm_id,NULL,0)) == (void *)-1)
        ERR("shmat");
    umask(sval);
    
    return ret;
}


void print_time()
{
	time_t timestamp;
	struct tm *showtime;

	time(&timestamp);
    showtime = localtime(&timestamp);
    printf("%02d:%02d:%02d -- %d client connected\n",showtime->tm_hour,showtime->tm_min,showtime->tm_sec,*client_count);
}


int main(int argc,const char **argv)
{
	int server_fd,reuse=0,cpid,ret;

	struct sockaddr_in server_sock;
	struct sockaddr_in client_sock;

	
	memset(&server_sock,0,sizeof(server_sock));
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(8080);
	
    //获取socket
	if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == -1)
		ERR("server_fd");
    //绑定server_fd
    if(bind(server_fd,(struct sockaddr *)&server_sock,sizeof(server_sock)) == -1)
        ERR("bind");
    //设置server_fd端口可以被重复使用
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)) == -1)
        ERR("setsockopt");
    //监听server_fd
	if(listen(server_fd,MAXCONNECT) == -1)
		ERR("listen");
    //设置连接计数器
    if((client_count = (int *)set_client_count(argv[0])) == NULL)
        ERR("set_client_count");
    *client_count = 0;



Listen:
    printf("Listening...\n");
    do{
        client_fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);  //等待客户端连接
    }while(client_fd == -1);

    (*client_count)++;	//更新连接计数器
	print_time();

    cpid = fork();  //开辟子进程与客户端通信
    if(cpid == -1){
        ERR("fork");
	}
    else if(cpid == 0){
        send(client_fd,buf,BUFSIZE,0);

		//等待client输入命令
		while(strncmp(cmd,"quit",4) != 0){
			ret = wait_for_input(client_fd,600);
			if(ret == 1){
				recv(client_fd,cmd,BUFSIZE,0);
				printf("%s\n",cmd);
				dispatch();
			}
			else
				break;
		}
		close(client_fd);
		(*client_count)--;	//更新连接计数器
		print_time();
		return 0;
    }
    else{
        close(client_fd);
        if(*client_count >= MAXCONNECT){
            printf("Too many clients,stop listening\n");
            while(*client_count >= MAXCONNECT); //如果超过最大连接数，则阻塞等待已连接的client退出
        }
        goto Listen;    //父进程关闭client_fd，继续listen
    }
	
	return 0;
}


