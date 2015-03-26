#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#define MSGSIZE 128

int main()
{

	int pipefd[2];
	pid_t cpid1,cpid2;
	char buf[MSGSIZE];

	//生成pipe
	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(errno);
	}
	//第一个child，关闭pipefd[0]，写pipefd[1]
	cpid1 = fork();
	if(cpid1 == -1){
		perror("child1");
		exit(errno);
	}
	else if(cpid1 == 0){
				close(pipefd[0]);
				write(pipefd[1],"Child 1 is sending a message!",MSGSIZE);
				close(pipefd[1]);
    }
	else{
        //第二个child，关闭pipefd[0]，等待child1返回，然后写pipefd[1]
        cpid2 = fork();
        if(cpid2 == -1){
            perror("child2");
            exit(errno);
        }
        else if(cpid2 == 0){
            close(pipefd[0]);
            wait(cpid1,NULL,0);
            write(pipefd[1],"Child 2 is sending a message!",MSGSIZE);
            close(pipefd[1]);
        }
        else{
            close(pipefd[1]);
            read(pipefd[0],buf,MSGSIZE);
            printf("%s\n",buf);
            read(pipefd[0],buf,MSGSIZE);
            printf("%s\n",buf);
            close(pipefd[0]);
        }
	}

	return 0;
}






