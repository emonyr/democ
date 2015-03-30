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
#define SEMKEY 0x10





int main()
{

	int myshm_id,mysemid;
	void *myshm_addr;
	char buf[STRSIZE];
	struct sembuf down;
	down.num = 0;
	down.op = -1;
	down.num = SEM_UNDO;
	struct sembuf up;
	up.num = 0;
	up.op = 1;
	up.num = SEM_UNDO;

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
	//获取semaphore id并初始化值为1
    mysemid = semget(SEMKEY,1,IPC_CREAT|IPC_NOWAIT|0666);
	if(mysemid == -1){
		perror("semget");
		exit(errno);		
	}
    semctl(mysemid,1,SETVAL);
	
	semop(mysemid,&down,1);
		printf("Please input a msg(lenth<=%d)\n",STRSIZE);
		fgets(buf,STRSIZE,stdin);
		memcpy(myshm_addr,buf,STRSIZE);
		printf("input success:%s\n",buf);
		pause();
	semop(mysemid,&up,1);
	shmdt(myshm_addr);

    return 0;
}




