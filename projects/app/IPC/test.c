#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#define STRSIZE 24
#define SHMKEY 0x23
#define SEMKEY 0x339478



int main()
{

	int mysemid;
	union semun mysemun = 1;
	struct sembuf down = {0,-1,SEM_UNDO};
	struct sembuf up = {0,1,SEM_UNDO};

	mysemid = semget(SEMKEY,1,IPC_CREAT|0666);
	if(mysemid == -1){
		perror("semget");
		exit(errno);		
	}
	printf("%d\n",mysemid);
	semctl(mysemid,0,GETVAL);
	printf("%d\n",mysemun.val);
	
	semop(mysemid,&down,1);
		printf("this is a test\n");
		sleep(10);
	semop(mysemid,&up,1);
    return 0;
}




