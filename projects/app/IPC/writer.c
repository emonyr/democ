/*
* writer 用于从标准输入获取STRSIZE长度的信息
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
#define SEMKEY 54321

key_t mysemid;
struct sembuf sem_down = {0,-1,0};
struct sembuf sem_up = {0,1,0};

void down()
{
	semop(mysemid,&sem_down,1);
}

void up()
{
	semop(mysemid,&sem_up,1);
}

int main()
{

	int myshm_id;
	void *myshm_addr;
	char buf[STRSIZE];


	//从内核空间分配shm
	myshm_id = shmget(SHMKEY,STRSIZE,IPC_CREAT|0666);
	if (myshm_id == -1) {
		perror("shmget");exit(errno);
	}
	//绑定shm到用户空间
	myshm_addr = shmat(myshm_id,NULL,0);
	if (myshm_addr == (void *)-1) {
		perror("shmat");exit(errno);
	}
	
	//获取semaphore id
    mysemid = semget(SEMKEY,1,IPC_CREAT|0666);
	if(mysemid == -1){
		perror("semget");exit(errno);		
	}
    
	down();
	printf("Please input a msg(lenth<=%d)\n",STRSIZE);
	fgets(buf,STRSIZE,stdin);
	memcpy(myshm_addr,buf,STRSIZE);
	printf("input success:%s\n",buf);
	sleep(10);	//等待10秒以供reader读取信息
	shmdt(myshm_addr);
	up();
    return 0;
}




