/*
 * protocal.c 
 * 提供http协议相关的函数
 */

#include "global.h"

/*
 * all_to_lowercase 
 * 把buf内的字母转为小写
 */
int all_to_lowercase(char *buf)
{
	int i,len;
	len = strlen(buf);
	
	for(i=0;i<len;i++)
		buf[i] = tolower(buf[i]);

	return i == len ? 0:-1;
}


/*
 * dispatch
 * 根据请求类型分派任务
 */
int dispatch(int fd,char *buf)
{
	if(all_to_lowercase(buf) == -1)
		ERR("all_to_lowercase");
	if(strncmp(buf,"head",4) == 0)
		response_head(fd,buf);
    else if(strncmp(buf,"get",3) == 0)
		response_get(fd,buf);
    else if(strncmp(buf,"post",4) == 0)
		response_post(fd,buf);
    else if(strncmp(buf,"put",3) == 0)
		response_put(fd,buf);
	else if(strncmp(buf,"delete",6) == 0)
		response_delete(fd,buf);
    else
		response_error(fd,buf);
	
	close(fd);

	return 0;
}

int response_head(int fd,char *buf)
{
	print_time();
	printf("request type: GET\n");
	return 0;
}

int response_get(int fd,char *buf)
{
	print_time();
	printf("request type: GET\n");
	return 0;
}

int response_post(int fd,char *buf)
{
	
	return 0;
}

int response_put(int fd,char *buf)
{
	
	return 0;
}

int response_delete(int fd,char *buf)
{
	
	return 0;
}

int response_error(int fd,char *buf)
{
	
	return 0;
}


















