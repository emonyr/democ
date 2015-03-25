#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


pid_t driver,conductor;

//定义售票员的信号句柄
void conductor_handler(int sig)
{
    switch (sig) {
        case SIGINT:
            kill(driver,SIGUSR1);
            break;
        case SIGQUIT:
            kill(driver,SIGUSR2);
            break;
        case SIGUSR1:
            printf("conductor:please get off the bus\n");
            break;
        default:
            printf("unknown signal\n");
            break;
    }
}

//定义司机的信号句柄
void driver_handler(int sig)
{
    switch (sig) {
        case SIGUSR1:
            printf("driver:let’s gogogo\n");
            break;
        case SIGUSR2:
            printf("driver:stop the bus\n");
            break;
        case SIGTSTP:
            kill(conductor,SIGUSR1);
            break;
        default:
            printf("unknown signal\n");
            break;
    }
    
}


int main()
{
    
    driver = getpid();
    conductor = fork();
    if(conductor == -1){
        perror("child process");
        exit(errno);
    }
    else if(conductor == 0){
        signal(SIGINT,conductor_handler);
        signal(SIGQUIT,conductor_handler);
        signal(SIGUSR1,conductor_handler);
        pause();    //等待用户从shell输入相应的kill命令
    }
    else{
        sleep(1);
        signal(SIGTSTP,driver_handler);
        signal(SIGUSR1,driver_handler);
        signal(SIGUSR2,driver_handler);
        pause();    //等待用户从shell输入相应的kill命令
    }
    
    return 0;
}



