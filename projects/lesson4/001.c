#include <stdio.h>
#include <stdlib.h>

/*编码函数*/
unsigned int encode(unsigned char *dest,unsigned char *src,unsigned long len)
{
	if(dest == NULL || src == NULL || len == 0){
		perror("space error");
		exit(-1);
	}

	int i=1;
	unsigned char *in,*out;
	in = src;
	out = dest;

	while(in != (src+len)){
		*(out++) = *in;
		while(*in == *(++in)){
			i++;
		}
		*(out++) = i;
		i = 1;
	}
	return out - dest;
}

/*解码函数*/
void *decode(void *dest,void *src,unsigned long len)
{
	
}


int main()
{
	int i;
	unsigned int encode_size;
	unsigned char arr[15] = {0x11,0x11,0x11,0x11,0x22,0x33,0x33,0x33,0x33,0x44,0x44,0x55,0x55,0x55,0x55};
	unsigned char *encode_dest;
	encode_dest = (unsigned char *)calloc(1,sizeof(arr));
	
	encode_size = encode(encode_dest,arr,sizeof(arr));
	for(i=0;i<encode_size;i++){
		printf("%x ",encode_dest[i]);
	}
	printf("\n");
	free(encode_dest);
	return 0;
}






