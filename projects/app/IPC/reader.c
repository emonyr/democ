/*
* reader 用于从shared memory中获取STRSIZE长度的信息
*/
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/sem.h>
#define STRSIZE 24
#define SHMKEY 12345


int main()
{
	int myshm_id;
	void *myshm_addr;
	char buf[STRSIZE];

	//从内核空间分配shm
	myshm_id = shmget(SHMKEY,STRSIZE,IPC_CREAT|0666);
	if (myshm_id == -1) {
		perror("shmget");
		exit(errno);
	}
	//绑定shm到用户空间
	myshm_addr = shmat(myshm_id,NULL,0);
	if (myshm_addr == (void *)-1) {
		perror("shmat");
		exit(errno);
	}

	memcpy(buf,myshm_addr,STRSIZE);
	printf("read success:%s",buf);

    return 0;
}




