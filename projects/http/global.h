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
#define HOSTNAME 64
#define FILENAME 128

char request_buf[BUFSIZE];
char response_buf[BUFSIZE];

const char month_tab[12][3] =""Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"";
const char day_tab[7][3] = ""Sun","Mon","Tue","Wed","Thu","Fri","Sat"";


//defined in connection.c
extern int server_fd;
extern int creat_server_fd(const char *port);
extern void wait_for_connect(int *fd,struct sockaddr_in *addr,socklen_t *addrlen);
extern void print_time(void);
extern int wait_for_input(int fd,int time);
extern void handle_request(int fd);
extern int set_fd_flags(int fd,int new_flags);


//defined in protocal.c
struct request{
	char type[8];
	char hostname[HOSTNAME];
	char port[4];
	char filename[FILENAME];
}
extern int dispatch(int fd);
extern int response_head(int fd);
extern int response_get(int fd);
extern int response_post(int fd);
extern int response_put(int fd);
extern int response_delete(int fd);
extern int send_response(int fd,char *msg);

#endif

