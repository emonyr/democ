#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main()
{
	FILE *output;
	int lineno=1;
	struct tm *showtime;
    time_t *timep,mytime;

	

	output = fopen("test.txt","a+");
	if(!output){
		perror("open");
		exit(errno);
	}
	
    //计算文件中已存在的行数
    while(!feof(output)){
        if (fgetc(output) == '\n') {
            lineno++;
        }
    }
    
    timep = &mytime;
	while(1){
        time(timep);
		showtime = localtime(timep);
        showtime->tm_year += 1900;
        showtime->tm_mon += 1;
        fprintf(output,"%d, %d-%d-%d %d:%d:%d\n",lineno,showtime->tm_year,showtime->tm_mon,showtime->tm_mday,showtime->tm_hour,showtime->tm_min,showtime->tm_sec);
        fprintf(stdout,"%d, %d-%d-%d %d:%d:%d\n",lineno,showtime->tm_year,showtime->tm_mon,showtime->tm_mday,showtime->tm_hour,showtime->tm_min,showtime->tm_sec);
		lineno++;
		sleep(1);
	}
	
	fclose(output);
	return 0;
}