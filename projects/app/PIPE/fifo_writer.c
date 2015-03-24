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
	int writer_fd;
	char buf[BUFSIZE] = "Hello John";

	umask(0);
	writer_fd = open("FIFO",O_RDWR);
	if(!writer_fd){
		perror("open");
		exit(errno);	
	}

	write(writer_fd,buf,BUFSIZE);
	close(writer_fd);
	return 0;
}

