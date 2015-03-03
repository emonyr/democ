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
		out[*len++] = *in;	//�Ѳ��ظ���ֵ����tmp������tmp�����������һλ
		out = (unsigned char *)realloc(out,(*len)+1);
		while(*in == *(++in)){	//�Ƚ��������ֵ�������������������ۼ���������Ŀ��i
			i++;
		}
		out[*len] = i;	//����������Ŀ��i��ֵ��out
		out = (unsigned char *)realloc(out,(*len)+1);
		i = 1;	//����i
	}

	return out;	
}