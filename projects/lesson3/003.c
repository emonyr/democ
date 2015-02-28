#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*int_bitcount用于计算int空间中，值为1的位数*/
int int_bitcount(int input)
{
	int sum=0;
	while(input){
		sum += (input & 1);
		input >>= 1;	//输入值跟1进行与操作，累加到sum，并且不断让input右移1位直至为0
	}
	return sum;
}


/*void_bitcount用于计算任意空间中，值为1的位数*/
int void_bitcount(void *input,unsigned long size)
{
	int sum=0;
	unsigned char *p,*p_;
	//为了不损坏源数据，把输入的空间内容复制到malloc开辟的新空间，并且用p_保存新空间的地址以便使用过后释放
	p_ = memcpy(p = (unsigned char *)malloc(size),input,size);	
	

	while(size--){
		while(*p){
			sum += (*p & 1);
			*p >>= 1;	//同样，输入值跟1进行与操作，累加到sum，并且不断让input右移1位直至为0
		}
		p++;	//每次清算完一个字节，移动指针到下一字节，直至清算完size大小的空间
	}
	free(p_);
	return sum;
}

int main(int argc,const char **argv)
{
	int arr[2] = {0xf,0xff};
	printf("int_bitcount: There are %d '1' in arr[0]\n",int_bitcount(arr[0]));
	printf("void_bitcount: There are %d '1' in arr\n",void_bitcount(arr,sizeof(arr)));
	printf("void_bitcount: There are %d '1' in \"Hello\"\n",void_bitcount("Hello",sizeof("Hello")));
	return 0;
}





