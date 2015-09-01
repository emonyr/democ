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
	
	int i;
	pthread_t worker[POOLSIZE];
	struct request *new;
	
	//建立服务器端socket
	creat_server_fd(argv[1]);
	//初始化request等待列表头
	queue = list_init();
	//初始化读写锁
	pthread_mutex_init(&lock,NULL);
	//创建buf_end key
	pthread_key_create(&buf_end_key, NULL);
	//初始化线程池
	for(i=0;i<POOLSIZE;i++)
		pthread_create(&worker[i],NULL,handle_request,NULL);
	
wait:
	new = wait_for_connect();
	pthread_mutex_lock(&lock);
	list_push(queue,new);
	pthread_mutex_unlock(&lock);
	goto wait;
	
	return 0;
}