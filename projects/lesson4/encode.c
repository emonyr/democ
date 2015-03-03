#include <stdio.h>
#include <stdlib.h>

void *encode(const void *raw,int *len)
{
	if(raw == NULL){
		perror("space error");
		exit(-1);
	}

	int i=1,end_offset=*len;
	unsigned char *in,*out;
	in = (unsigned char *)raw;
	out = (unsigned char *)malloc(1);
	if(!out){
		perror("malloc");
		exit(-1);
	}
	
	for((*len)=0;in != (raw+end_offset);*len++){
		out[*len++] = *in;	//把不重复的值赋给tmp，并让tmp跳到数组的下一位
		out = (unsigned char *)realloc(out,(*len)+1);
		while(*in == *(++in)){	//比较相邻项的值，如果相等则跳过，并累计跳过的项目数i
			i++;
		}
		out[*len] = i;	//把跳过的项目数i赋值给out
		out = (unsigned char *)realloc(out,(*len)+1);
		i = 1;	//重置i
	}

	return out;	
}