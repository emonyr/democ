#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFSIZE 512

int main()
{
	int fifofd;
	char buf[BUFSIZE];


	//建立有名管道
	umask(0);
	if(mkfifo("FIFO",0666) == -1){
		perror("mkfifo");
		exit(errno);
	};

	fifofd = open("FIFO",O_RDONLY);
	if(!fifofd){
		perror("open");
		exit(errno);
	}
	//死循环等待另一端写入
	while(1){
		read(fifofd,buf,BUFSIZE);
		buf[BUFSIZE-1] = '\0';
		printf("%s\n",buf);
	}
	close(fifofd);
	return 0;
}

