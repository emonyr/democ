#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#define STRSIZE 24


int main(int argc,const char *argv[])
{
	key_t mykey = ftok(argv[0],9001);
	void *myshm_addr;
	char buf[STRSIZE];


	shmget(mykey,STRSIZE,IPC_PRIVATE|0666);
	myshm_addr = shmat(mykey,NULL,0);
	printf("Please input a msg(lenth=%d)\n",STRSIZE);
	gets(buf);
	printf("buf:%s\n",buf);
	memcpy(myshm_addr,buf,STRSIZE);
	shmdt(myshm_addr);
	printf("myshm_addr:%s\n",(char *)myshm_addr);
	return 0;
}
