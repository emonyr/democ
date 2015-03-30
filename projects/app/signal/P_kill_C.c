#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


void sig_handler1(int signo)
{
    if (signo == SIGINT) {
        printf("Child process 1 is killed by parent!\n");
    }

}

void sig_handler2(int signo)
{
    if (signo == SIGINT) {
        printf("Child process 2 is killed by parent!\n");
    }
    
}


int main()
{
    pid_t child1,child2;
    
    //parent获取第一个child
    child1 = fork();
    if(child1 == -1){
	perror("child1");
	exit(errno);
    }
    else if(child1 == 0){   //这里是child1
            signal(SIGINT,sig_handler1);
            waitpid(child2,NULL,0);
            pause();
        }
    
    else{   //回到parent获取第二个child
        child2 = fork();
        if(child2 == -1){
            perror("child2");
            exit(errno);
        }
        else if(child2 == 0){   //这里是child2
            signal(SIGINT,sig_handler2);
            pause();
        }
    
        else{   //再回到parent发出信号
            sleep(1);
            kill(child2,SIGINT);
            waitpid(child2,NULL,0);
            kill(child1,SIGINT);
            waitpid(child1,NULL,0);
            printf("Parent process exit!\n");
        }
    }
    return 0;
}






