#include <stdio.h>
#include <stdlib.h>


//这个结构体用于存放字符串的长度与空格数
struct strcount{
	unsigned int length;
	unsigned int space;
};	

struct strcount * do_count(const char *p)
{
	struct strcount *s ;
	s = malloc(sizeof(struct strcount));	//申请用于存放strcount的空间，稍后在main()里释放
	
	if(p == NULL)
	{
		printf("Please input a valid string.\n");
		exit(1);
	}

	while(*p++) 
	{
		s->length++;	//累计字符数
		if(*p == ' ')
			s->space++;	//累计空格数
	}
	return s;
}


int main(int argc,const char **argv)
{
	if(argc != 2)
	{
		printf("Usage : %s + \"String\"\n",argv[0]);
		exit(1);
	}	
	
	struct strcount *pstr;
	pstr = do_count(argv[1]);	//调用do_count()函数，返回strcount结构体指针
	printf("length : %u\nspace : %u\n",pstr->length,pstr->space);
	free(pstr);
	return 0;
}







