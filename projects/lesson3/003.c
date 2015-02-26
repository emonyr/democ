#include <stdio.h>
#include <string.h>
#include <stdlib.h>

union uchar_box{
	unsigned char *p;
	unsigned char *p_;
};

int int_bitcount(unsigned int input)
{
	int sum;
	while(input >>= 1){
		if(input & 1)
			sum++;
	}
	return sum;
}

int void_bitcount(void *input,unsigned long size)
{
	int sum;
	union uchar_box box = {.p = memcpy(malloc(size),input,size)};
	
	
	printf("%lu\n",size);
	while(size--){
		while(*(box.p)){
			if(*(box.p) & 1)
				sum++;
			*(box.p) >>= 1;
		}
		(box.p)++;
	}
	free(box.p_);
	return sum;
}

int main(int argc,const char **argv)
{
	if(argc != 2){
		printf("Usage: %s + [content]\n",argv[0]);
		exit(1);
	}

	printf("int_bitcount: there are %d '1'.\n",int_bitcount((unsigned int)atoi(argv[1])));
	printf("void_bitcount: there are %d '1'.\n",void_bitcount((void *)argv[1],sizeof(argv[1])));
	return 0;
}





