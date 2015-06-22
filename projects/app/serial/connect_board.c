#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#define ERR(x) {perror(x);exit(errno);}
#define BUFSIZE 512

int fd;

void sig_exit_handler(int signum)
{
	if(signum == SIGINT || signum == SIGTERM){
		close(fd);
		ERR("Quit.\n");
	}
	exit(1);
}

int wait_for_input(int filedes,int time)
{
	
	fd_set readfds;
	struct timeval tv;
	
	//设置select fd_set
	FD_ZERO(&readfds);
	FD_SET(filedes,&readfds);
	//等待10分钟
	tv.tv_sec = time;
	tv.tv_usec = 500;
	
	return select(FD_SETSIZE,&readfds,NULL,NULL,&tv);
	
}

int main(int argc,const char *argv[]){
	
	int cpid,nbyte,i;
	char buf,cmd[BUFSIZE];
	struct termios opt;
	
	//使用open函数打开串口，获得串口设备文件的文件描述符
	if((fd=open("/dev/ttys1",O_RDWR| O_NOCTTY))==-1){
		ERR("Cannot open the serial port.\n");
	}

	//关联串口和termio结构体
	tcgetattr(fd,&opt);
	//设置输入输出波特率
	cfsetispeed(&opt,B115200);
	cfsetospeed(&opt,B115200);
	//设置数据位
	opt.c_cflag &= ~CSIZE;
	opt.c_cflag |= CS8;
	//设置奇偶校验
	opt.c_cflag &= ~PARENB;
	//设置流控制
	opt.c_cflag &= ~CRTSCTS;
	//保存设置
	tcsetattr(fd,TCSANOW,&opt);
	
	cpid = fork();  //开辟子进程与客户端通信
	if(cpid == -1){
		ERR("fork");
	}
	else if(cpid == 0){
	Listen:
		while(wait_for_input(fd,6000) == 1){
			nbyte = read(fd,buf,1);
			write(STDOUT_FILENO,buf,1);
		}
	}
	else{
		while(1){
			printf("\n>");
			fgets(cmd,BUFSIZE,stdin);
			if((strncmp(cmd,"quit",4) == 0 )|| (strncmp(cmd,"exit",4) == 0 ))
				goto Out;
			while(cmd[i++]){
				write(fd,cmd[i],1);
			}
		}
	}
	goto Listen;
	
Out:
	close(fd);
	
	return 0;
}