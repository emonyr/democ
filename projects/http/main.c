/*
 * main.c 
 * jyserver主函数，负责启动server，开辟子进程处理请求，循环接受连接
 */

#include "global.h"

int main(int argc,const char *argv[])
{
	if (argc != 2){
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		return -1;
	}
	
	int i=0,server_fd;
	pthread_t worker[POOLSIZE];

	
	//建立服务器端socket
	server_fd = creat_server_fd(argv[1]);
	//初始化读写锁
	pthread_mutex_init(&lock,NULL);
	//创建key文件
	pthread_key_create(&buf_end_key, NULL);
	//创建无名管道作为request队列
	pipe(pipefd);
	//初始化线程池
	for(i=0;i<POOLSIZE;i++)
		pthread_create(&worker[i],NULL,handle_request,NULL);

	wait_for_connect(server_fd);

	return 0;
}


