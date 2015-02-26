#include <stdio.h>
#include <stdlib.h>
#define ARR_SIZE 10
#define ARR_CONTENT {1,2,3,4,5,6,7,8,9,10}
#define STR_SIZE 1024
#define USAGE_ERROR printf("Usage : %s -[rd] [number/string]\n",argv[0])


int a[ARR_SIZE] = ARR_CONTENT;
char mystr[STR_SIZE];


/*此函数把前n个数字逆序*/
void nreverse(int *input,int n)	
{
	int i;
	unsigned long len = sizeof(a)/sizeof(int);	//计算数组元素数量

	//打印原始数组
	printf("Original array :\n");
	for(i=0;i<len;i++) 
		printf("%d,",a[i]);
	printf("\n");
	if(n>len){
		printf("Please input a number smaller than %lu.\n",len);
		exit(1);
	}
	
	
	//进行逆序操作
	int tmp[--n];	//因为数组是从tmp[0]开始的，所以n必须先减去1
	for(i=0;n>=0;n--,i++)
		tmp[i] = input[n];		
	for(n=0;n<i;n++)
		input[n] = tmp[n];	
	
	
	//打印逆序后的数组
	printf("Reversed array :\n");
	for(i=0;i<len;i++) printf("%d,",a[i]);
	printf("\n");
}



/*此函数打印出删除空格后的字符串*/
void del_space(const char *p)
{
	if(p == NULL){
		printf("Please input a valid string.\n");
		exit(1);
	}
	
	int i = 0;
	while(*p){
		if(*p == ' ' || *p == '	'){
			p++;			
			continue;	//跳过空格和制表符
		}
		mystr[i] = *p;
		i++;
		p++;
	}
	printf("%s\n",mystr);
}


int main(int argc,const char **argv)
{
	if(argc<3){
		USAGE_ERROR;
		exit(1);
	}
	
	if(argv[1][1] == 'r') 
		nreverse(a,atoi(argv[2]));	//输入-r，则调用nreverse()
	else if(argv[1][1] == 'd')
		del_space(argv[2]);		//输入-d，则调用del_space()
	else{
		USAGE_ERROR;
		exit(1);
	}

	return 0;
}







