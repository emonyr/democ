#include <stdio.h>


int main()
{
	fprintf(stdout,"hello1");
	while(1);
	fprintf(stdout,"hello1\n");
	fprintf(stderr,"hello2");
	fprintf(stderr,"hello2\n");
	
	return 0;
}