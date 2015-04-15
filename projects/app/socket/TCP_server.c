#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
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
#define BUFSIZE 1024
#define CMDSIZE 512
#define MAXCONNECT 10

int client_fd,*client_count;
socklen_t client_len;
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
    while(s[i])
        arg[j++] = s[i++];
    
    if(j == 0){
        printf("getarg failed: void arg\n");exit(1);
    }
    
    return arg;
}

int cmd_help()
{
    if(send(client_fd,"Usage:\n\thelp\n\tlist\n\tget <file>\n\tput <file>\n\tquit\n",CMDSIZE,0) == -1){
        perror("send help");
    }
    return 0;
}

int filter(const struct dirent *d)
{
    return 1;
}

int cmd_list()
{
    int count,i;
    struct dirent **namelist;
    
    count = scandir(".",&namelist,filter,alphasort);
    if(count == -1){
        perror("scandir");
    }
    for(i=0;i<count;i++){
        send(client_fd,namelist[i]->d_name,BUFSIZE,0);
    }
    
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
	while(lseek(content,0,SEEK_CUR) != SEEK_END){
        read(content,buf,BUFSIZE);
        if(send(client_fd,buf,BUFSIZE,0) == -1)
            perror("send file");
    }
    umask(sval);
    close(content);
    
    return 0;
}

int cmd_put()
{
	int content,sval;
    getarg(cmd);
	
    umask(0);
    content = open(arg,O_RDWR|O_APPEND|O_CREAT|O_TRUNC,0666);
    if(content < 0){
        send(client_fd,"failed to create file on server.\n",BUFSIZE,0);
        exit(1);
    }
    
    while(recv(content,buf,BUFSIZE,0));
    umask(sval);
    close(content);
	
    return 0;
}


int dispatch() //根据cmd分派任务
{
    if(strncmp(cmd,"help",4) == 0)
        cmd_help();
    else if(strncmp(cmd,"list",4) == 0)
        cmd_list();
    else if(strncmp(cmd,"get",3) == 0)
        cmd_get();
    else if(strncmp(cmd,"put",3) == 0)
        cmd_put();
    else if(send(client_fd,"Unknown command\nInput \"help\" for more information\n",CMDSIZE,0) == -1){
        ERR("send Unknown command");
    }
    return 0;
}

void *set_client_count(const char *filename)    //实现连接计数器
{
    int shm_id;
    void * ret;
    
    umask(0);
    //从内核空间分配shm
    shm_id = shmget(ftok(filename,'a'),sizeof(int),IPC_CREAT|0666);
    if (shm_id == -1) {
        perror("shmget");exit(errno);
    }
    //绑定shm到用户空间
    ret = shmat(shm_id,NULL,0);
    if (ret == (void *)-1) {
        perror("shmat");exit(errno);
    }
    umask(0002);
    
    return ret;
}



int main(int argc,const char **argv)
{
	int server_fd,reuse=0,cpid;
    time_t timestamp;
    struct tm *showtime;

	struct sockaddr_in server_sock;
	struct sockaddr_in client_sock;
	
	server_sock.sin_family = AF_INET;
	server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
	server_sock.sin_port = htons(8080);
	
    //获取socket
    server_fd = socket(AF_INET,SOCK_STREAM,0);
	if(server_fd == -1){
		ERR("server_fd");
	}
    //绑定server_fd
    if(bind(server_fd,(struct sockaddr *)&server_sock,sizeof(server_sock)) == -1){
        ERR("bind");
    }
    //设置server_fd端口可以被重复使用
    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse)) == -1){
        ERR("setsockopt");
    }
    //监听server_fd
	if(listen(server_fd,MAXCONNECT) == -1){
		ERR("listen");
	}
    //设置连接计数器
    client_count = (int *)set_client_count(argv[0]);
    if(!client_count){
        ERR("set_client_count");
    }
    *client_count = 0;
    


Listen:
    printf("Listening...\n");
    do{
        client_fd = accept(server_fd,(struct sockaddr *)&client_sock,&client_len);  //等待客户端连接
    }while(client_fd == -1);
    (*client_count)++;
    time(&timestamp);
    showtime = localtime(&timestamp);
    printf("%02d:%02d:%02d -- %d client connected\n",showtime->tm_hour,showtime->tm_min,showtime->tm_sec,*client_count);
    
    cpid = fork();  //开辟子进程与客户端通信
    if(cpid == -1){
        ERR("fork");
    }
    else if(cpid == 0){
        if(send(client_fd,"Welcome to Johnny's server!\n\nPlease input a command.\n",CMDSIZE,0) == -1){
            ERR("send welcome");
        }
        while(strncmp(cmd,"quit",4) != 0){
            while(recv(client_fd,cmd,CMDSIZE,0) == -1);
            dispatch();
        }
        close(client_fd);
        (*client_count)--;
        printf("Client quit.\n");
        time(&timestamp);
        showtime = localtime(&timestamp);
        printf("%02d:%02d:%02d -- %d client connected\n",showtime->tm_hour,showtime->tm_min,showtime->tm_sec,*client_count);
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


