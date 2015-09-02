/*
 * global.h
 * 全局变量表
 */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <pthread.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>


#ifdef __DEBUG__
#define ERR(x) ({perror(x);pthread_exit();})
#else
#define ERR(x) 
#endif

#define ROOT "./www"
#define CGITMP "./www/cgi-bin/tmp"
#define NOT_FOUND "HTTP/1.1 400 Bad Request\r\n\r\n404 not found"

#define POOLSIZE 16
#define BACKLOGSIZE	1024
#define BUFSIZE	8192
#define HOSTLEN 64
#define FILELEN 128

//for main.c
char GMTtime[30];
pthread_mutex_t lock;
struct request *queue;
int pipefd[2];


//for connection.c
extern int server_fd;
extern int creat_server_fd(const char *port);
extern struct request * wait_for_connect(void);
extern char * current_time(void);
extern int wait_to_read(int fd,int seconds);
extern int wait_to_write(int fd,int seconds);
extern void * handle_request(void *);
extern int set_fd_flags(int fd,int new_flags);


//for protocal.c
struct request{
	int fd;
	char type[8];
	char hostname[HOSTLEN];
	char port[4];
	char filename[FILELEN];
	char filetype[12];
	char request_buf[BUFSIZE];
	char response_buf[BUFSIZE];
};
pthread_key_t buf_end_key;

extern int dispatch(struct request *req);
extern int response_get(struct request *req);
extern int response_post(struct request *req);
extern int response_put(struct request *req);
extern int response_delete(struct request *req);
extern int send_response(int fd,char *msg);
extern int all_to_lowercase(char *buf);
extern int read_request(struct request *req) ;
extern int print_to_buf(char *buf,const char *format,char *str);
extern int handle_cgi(struct request *req);


#endif

