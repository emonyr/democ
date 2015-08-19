/*
 * global.h
 * 全局变量表
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#ifdef __DEBUG__
#define ERR(x) do{perror(x);exit(errno);} while(0)
#else
#define ERR(x) do{} while(0)
#endif

#define ROOT "./www/"
#define CGIROOT "./www/cgi-bin/"

#define BACKLOGSIZE	1024
#define BUFSIZE	8192

char request_buf[BUFSIZE];
char response_buf[BUFSIZE];

extern int server_fd;

//for connection.c
extern int creat_server_fd(const char *port);
extern void wait_for_connect(int *fd,struct sockaddr_in *addr,socklen_t *addrlen);
extern void print_time(void);
extern int wait_for_input(int fd,int time);
extern void handle_request(int fd);
extern int set_fd_flags(int fd,int new_flags);


//for protocal.c
extern int dispatch(int fd,char *buf);
extern int response_head(int fd,char *buf);
extern int response_get(int fd,char *buf);
extern int response_post(int fd,char *buf);
extern int response_put(int fd,char *buf);
extern int response_delete(int fd,char *buf);
extern int response_error(int fd,char *buf);