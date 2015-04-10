#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,const char **argv)
{
    int file_fd;
    char buf[BUFSIZE];
    
    //实现r
    file_fd = open(argv[1],O_RDONLY);
    close(file_fd);
    //实现r+
    file_fd = open(argv[1],O_RDWR);
    close(file_fd);
    //实现w
    file_fd = open(argv[1],O_WRONLY|O_TRUNC|CREAT);
    close(file_fd);
    //实现w+
    file_fd = open(argv[1],O_RDWR|O_TRUNC|CREAT);
    close(file_fd);
    //实现a
    file_fd = open(argv[1],O_WRONLY|O_APPEND|O_CREAT);
    close(file_fd);
    //实现a+
    file_fd = open(argv[1],O_RDWR|O_APPEND|O_CREAT);
    close(file_fd);
    
    
    return 0;
}