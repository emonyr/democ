/*
* sem_init 用于初始化信号量，并避免writer调用semctl重置信号量的值
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


int main(int argc,char **argv)
{

	int mysemid,sval=1;

	union semun{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *__buf;
	}arg;
	arg.val = sval;

	
	//获取semaphore id并初始化值为1
    mysemid = semget(SEMKEY,1,IPC_CREAT|0666);
	if(mysemid == -1){
		perror("semget");exit(errno);		
	}
    
	if(semctl(mysemid,0,SETVAL,arg) == -1){
		perror("semctl");exit(errno);
	}
		
    return 0;
}




