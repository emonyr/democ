#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
//#define LINELEN 1024

int main(int argc,const char **argv)
{
	if(argc != 3){
		printf("Usage: %s + inputfile + outputfile\n",argv[0]);
		exit(errno);
	}
	
	FILE *input,*output;
	char buf;
	
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
		fputc(fgetc(input),output);
	}

	fclose(input);
	fclose(output);
	return 0;
}