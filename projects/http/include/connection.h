#include <sys/types.h>
#include <sys/socket.h>

#define MAXCONNECT	500
#define BUFSIZE	1024

char buf[BUFSIZE];

int server_fd = -1;

extern int creat_server_fd(const char port);
extern void wait_for_connect(void));
extern void print_time(void);
extern int wait_for_input(int fd,int time);
extern int handle_request(int fd);
