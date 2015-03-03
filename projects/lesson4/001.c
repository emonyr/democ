#include <stdio.h>
#include <stdlib.h>
#include "encode.c"
#include "decode.c"
#define ARR_SIZE(name) (sizeof(name)/sizeof(name[0]))

void *encode(const void *raw,int *len);
void *decode(const void *raw,int *len);

int main()
{
	int i,len;
	unsigned char arr[] = {0x11,0x11,0x11,0x22,0x33,0x33,0x33,0x44,0x44,0x55,0x55,0x55,0x55,0x55};
	unsigned char *compressed_data,*decompressed_data;
	len = ARR_SIZE(arr);

	//编码
	compressed_data = (unsigned char *)encode(arr,&len);
	for(i=0;i<len;i++){
		printf("%x ",compressed_data[i]);
	}
	printf("\n");

	//解码
	decompressed_data = (unsigned char *)decode(compressed_data,&len);
	for(i=0;i<len;i++){
		printf("%x ",decompressed_data[i]);
	}
	printf("\n");
	
	//再次编码
	compressed_data = (unsigned char *)encode(decompressed_data,&len);
	for(i=0;i<len;i++){
		printf("%x ",compressed_data[i]);
	}
	printf("\n");
	
	free(compressed_data);
	free(decompressed_data);
	return 0;
}






