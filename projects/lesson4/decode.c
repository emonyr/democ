#include <stdio.h>
#include <stdlib.h>

void *decode(const void *raw,int *len)
{
	if(raw == NULL){
		perror("space error");
		exit(-1);
	}
	
	int i,end_offset=*len;
	unsigned char *in,*out;
	in = (unsigned char *)raw;
	out = (unsigned char *)malloc(1);
	if(!out){
		perror("malloc");
		exit(-1);
	}
	
	*len = 1;
	for(i=0;in != (raw+end_offset);i++){
		out[i++] = *in;
		out = realloc(out,(*len)+(*(in+1)));
		while((*(in+1))--){	//in+1ָ��encode�����е��ۼ���i
			out[i] = *in;
			*len++;
		}
		in += 2;	//inָ������һ�����ȡֵ
		*len++;
	}
	
	return out;
}