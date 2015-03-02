#include <stdio.h>
#include <stdlib.h>
#define	ARR_SIZE 15

/*编码函数*/
unsigned long encode(void *dest,void *src,unsigned long len)
{
	if(dest == NULL || src == NULL || len == 0){
		perror("space error");
		exit(-1);
	}

	int i=1;
	unsigned char *in,*out;
	in = (unsigned char *)src;
	out = (unsigned char *)dest;

	while(in != (src+len)){
		*(out++) = *in;	//把不重复的值赋给out，并让out跳到数组的下一位
		while(*in == *(++in)){	//比较相邻项的值，如果相等则跳过，并累计跳过的项目数i
			i++;
		}
		*(out++) = i;	//把跳过的项目数i赋值给out，并让out跳到数组的下一位
		i = 1;	//重置i
	}
	
	return (void *)out - dest;	//返回编码后数组的大小
}


/*解码函数*/
unsigned long decode(void *dest,void *src,unsigned long len)
{
	if(dest == NULL || src == NULL || len == 0){
		perror("space error");
		exit(-1);
	}
	
	int i=1;
	unsigned char *in,*out;
	in = (unsigned char *)src;
	out = (unsigned char *)dest;
	
	while(in != (src+len)){
		while((*(in+1))--){	//in+1指向encode函数中的累计数i
			*(out++) = *in;
		}
		in += 2;	//in指针跳过一项，继续取值
	}
	
	return (void *)out - dest;	//返回编码后数组的大小
}


int main()
{
	int i;
	unsigned int encode_size,decode_size;
	unsigned char arr[ARR_SIZE] = {0x11,0x11,0x11,0x22,0x33,0x0,0x33,0x33,0x44,0x44,0x55,0x55,0x55,0x55,0x55};	//不知道为什么输入的数组最后一项不能为0
	unsigned char *encode_out,*decode_out;
	//calloc分配用于接收输出的空间
	encode_out = (unsigned char *)calloc(1,ARR_SIZE);
	decode_out = (unsigned char *)calloc(1,ARR_SIZE);

	//编码
	encode_size = encode(encode_out,arr,sizeof(arr));
	for(i=0;i<encode_size;i++){
		printf("%x ",encode_out[i]);
	}
	printf("\n");

	//解码
	decode_size = decode(decode_out,encode_out,encode_size);
	for(i=0;i<decode_size;i++){
		printf("%x ",decode_out[i]);
	}
	printf("\n");

	//再次编码
	encode_size = encode(encode_out,decode_out,decode_size);
	for(i=0;i<encode_size;i++){
		printf("%x ",encode_out[i]);
	}
	printf("\n");

	free(decode_out);
	free(encode_out);
	
	return 0;
}






