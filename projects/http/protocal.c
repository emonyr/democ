/*
 * protocal.c 
 * 提供http协议相关的函数
 */

#include "global.h"

int buf_end = 0;


/* dispatch() 根据请求类型分派任务 */
int dispatch(int fd)
{	
	if(all_to_lowercase(buf) == -1)
		ERR("all_to_lowercase");
	
    //把request_buf读取到request结构体
	struct request *s;
	s = (struct request *)malloc(sizeof(struct request));
	memset(s,0,sizeof(struct request));
	if(read_request(s) == -1){
		send_response(fd,"HTTP/1.1 400 Bad Request\r\n");
		free(s);
		close(fd);
	}
	
	//通过结构体的type识别请求方法
	memset(response_buf,0,BUFSIZE);
	if(strncmp(s->type,"get",3) == 0)
		response_get(fd,s);
	else if(strncmp(s->type,"head",4) == 0){
		response_head(fd,s);
		print_to_buf(response_buf,"\r\n");
	}
    else if(strncmp(s->type,"post",4) == 0)
		response_post(fd,s);
    else if(strncmp(s->type,"put",3) == 0)
		response_put(fd,s);
	else if(strncmp(s->type,"delete",6) == 0)
		response_delete(fd,s);
    else{
		send_response(fd,"HTTP/1.1 400 Bad Request\r\n");
		free(s);
		close(fd);
	}
	
	send_response(fd,response_buf);
	free(s);
	close(fd);

	return 0;
}

int response_get(int fd,struct request *s)
{
	response_head(fd,s);
	
	return 0;
}

int response_head(int fd,struct request *s)
{
	char current_time[29];
	
	print_to_buf(response_buf,"HTTP/1.1 200 OK\r\n");
	print_to_buf(response_buf,"Server: jyserver\r\n");
	print_to_buf(response_buf,"Date: ");
	sprintf(current_time,print_time());
	print_to_buf(response_buf,current_time);
	print_to_buf(response_buf,"\r\n");
	print_to_buf(response_buf,"Connection: Closed\r\n");
	
	return 0;
}

int response_post(int fd,struct request *s)
{
	
	return 0;
}

int response_put(int fd,struct request *s)
{
	
	return 0;
}

int response_delete(int fd,struct request *s)
{
	
	return 0;
}

int send_response(int fd,char *msg)
{
	send(fd,msg,strlen(msg),0);
	return 0;
}

static int print_to_buf(char *buf,char *str)
{
	sprintf(buf+buf_end,str);
	buf_end += strlen(str);
	if(buf_end>BUFSIZE)
		ERR("print_to_buf");
	return 0;
}

/* all_to_lowercase() 把buf内的字母转为小写 */
static int all_to_lowercase(char *buf)
{
	int i,len;
	len = strlen(buf);
	
	for(i=0;i<len;i++)
		buf[i] = tolower(buf[i]);

	return i == len ? 0:-1;
}

static int read_request(struct request *s) 
{
	int i=0,j=0;
	char *c;
	c = response_buf;
	
	//跳过空格
	while(*c == ' ')
		c++;
	
	//读取请求方法
    while((*c != ' ') && (i < 8)){
		s->type[i] = *c;
		c++;
		i++;
	}
	s->type[i] = '\0';
	
	//读取hostname
	while(*c != '/')
		c++;
	while(*c == '/')
		c++;
	if(*c == ' ')
		s->filename = "./www/index.html";
	else{
		i=2;
		s->filename[0] = '.';
		s->filename[1] = '/';
		while(*c != ' ')
			s->filename[i] = *c;
			c++;
			i++;
		}
		s->filename[i] = '\0';
	}

    return 0;
}





