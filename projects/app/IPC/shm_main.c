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

int shm_w();
int shm_r();


int main()
{
    int mysemid,child;
    struct sembuf down = {0,-1,0};
    struct sembuf up = {0,1,0};
    
    mysemid = semget(SEMKEY,1,IPC_CREAT|0666);
    semctl(mysemid,1,SETVAL);
    semop(mysemid,&down,1);
    shm_w();
    child = fork();
    if (fork()) {
        semop(mysemid,&up,1);
    }
    else{
        shm_r();
    }
    return 0;
}