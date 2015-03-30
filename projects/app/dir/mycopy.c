#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define MAXLEN 512

int main(int argc,const char **argv)
{
	if(argc<3){
		printf("Usage: %s + inputfile + outputfile\n",argv[0]);
		exit(errno);
	}
	
	FILE *input,*output;
	char buf[MAXLEN];
	
	input = fopen(argv[1],"r");
	if(!input){
		perror("open input");
		exit(errno);
	}
	output = fopen(argv[2],"w+");
	if(!output){
		perror("open output");
		exit(errno);
	}
	
	while(!feof(input)){
		fread(buf,1,MAXLEN,input);
		fwrite(buf,1,MAXLEN,output);
	}

	fclose(input);
	fclose(output);
	return 0;
}