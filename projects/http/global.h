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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <pthread.h>


#ifdef __DEBUG__
#define ERR(x) do{perror(x);pthread_exit(errno);} while(0)
#else
#define ERR(x) do{} while(0)
#endif

#define ROOT "./www"
#define CGITMP "./www/cgi-bin/tmp"
#define NOT_FOUND "HTTP/1.1 400 Bad Request\r\n\r\n404 not found"

#define POOLSIZE 4
#define BACKLOGSIZE	1024
#define BUFSIZE	8192
#define HOSTLEN 64
#define FILELEN 128

//#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
//#define container_of(ptr, type, member) ({const typeof(((type *)0)->member) *__mptr = (ptr);(type *)((char *)__mptr - offsetof(type,member));})


char GMTtime[30];
pthread_rwlock_t lock;

//for list.c
struct list_node{
	struct list_node *prev;
	struct list_node *next;
};
struct list_node *queue;
extern struct list_node * list_init(void);
extern struct list_node * list_push(struct list_node *head);
extern struct list_node * list_pop(struct list_node *head);


//for connection.c
extern int server_fd;
extern int creat_server_fd(const char *port);
extern struct request * wait_for_connect(void);
extern char * current_time(void);
extern int wait_for_input(int fd,int time);
extern void * handle_request(void *);
extern int set_fd_flags(int fd,int new_flags);


//for protocal.c
struct request{
	struct list_node *node;
	int fd;
	char type[8];
	char hostname[HOSTLEN];
	char port[4];
	char filename[FILELEN];
	char filetype[12];
	char *buf;
	char *response_buf;
};

extern int dispatch(struct request *req);
extern int response_get(struct request *req);
extern int response_post(struct request *req);
extern int response_put(struct request *req);
extern int response_delete(struct request *req);
extern int send_response(int fd,char *msg);
extern int all_to_lowercase(char *buf);
extern int read_request(struct request *req,char *request_buf) ;
extern int print_to_buf(char *buf,const char *format,char *str);
extern int handle_cgi(struct request *req);


#endif

