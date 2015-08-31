/*
 * protocal.c 
 * 提供http协议相关的函数
 */

#include "global.h"


/* dispatch() 根据请求类型分派任务 */
int dispatch(struct request *req)
{	
	int buf_end;
	//获得buf_end key
	pthread_setspecific(buf_end_key,&buf_end);
	//通过结构体的type识别请求方法
	char response_buf[BUFSIZE];
	memset(response_buf,0,BUFSIZE);
	req->response_buf = response_buf;
	if((strcmp(req->type,"get") == 0) || (strcmp(req->type,"head") == 0))
		response_get(req);
    else if(strcmp(req->type,"post") == 0)
		response_post(req);
    else if(strcmp(req->type,"put") == 0)
		response_put(req);
	else if(strcmp(req->type,"delete") == 0)
		response_delete(req);
    else
		print_to_buf(req->response_buf,NOT_FOUND,NULL);
	
	send_response(req->fd,req->response_buf);
	close(req->fd);
	free(req->buf);
	free(req);

	return 0;
}

int response_get(struct request *req)
{
	int resoucefd,nbytes,buf_end;
	char filesize[32];
	struct stat sb;
	
	printf("%s - Processing GET request: pid = %d , req->filename: %s\n",current_time(),(int)pthread_self(),req->filename);
	
	stat(req->filename,&sb);
	if(sb.st_mode & S_IXUSR)
		handle_cgi(req);
	
	resoucefd = open(req->filename,O_RDONLY,0666);
	if(resoucefd == -1){
		print_to_buf(req->response_buf,NOT_FOUND,NULL);
		perror("open");
		return -1;
	}
	sprintf(filesize,"%d",(int)lseek(resoucefd,0,SEEK_END));

	
	buf_end = *(int *)pthread_getspecific(buf_end_key);
	print_to_buf(req->response_buf,"HTTP/1.1 200 OK\r\n",NULL);
	print_to_buf(req->response_buf,"Server: jyserver\r\n",NULL);
	print_to_buf(req->response_buf,"Date: %s\r\n",GMTtime);
	print_to_buf(req->response_buf,"Connection: Closed\r\n",NULL);
	print_to_buf(req->response_buf,"Content-Length: %s\r\n",filesize);
	print_to_buf(req->response_buf,"Content-Type: text/html\r\n",NULL);
	print_to_buf(req->response_buf,"Cache-Control: no-cache\r\n",NULL);
	print_to_buf(req->response_buf,"\r\n",NULL);
	if(strcmp(req->type,"head") == 0)
		return 0;
	
	lseek(resoucefd,0,SEEK_SET);
	while(nbytes != 0){
		nbytes = read(resoucefd,&req->response_buf[buf_end],1024);
		buf_end = buf_end + nbytes;
	}
	close(resoucefd);
	
	if(strcmp(req->filetype,"cgi") == 0)
		unlink(req->filename);
	
	return 0;
}

int response_post(struct request *req)
{
	//reserved
	print_to_buf(req->response_buf,NOT_FOUND,NULL);
	return 0;
}

int response_put(struct request *req)
{
	//reserved
	print_to_buf(req->response_buf,NOT_FOUND,NULL);
	return 0;
}

int response_delete(struct request *req)
{
	//reserved
	print_to_buf(req->response_buf,NOT_FOUND,NULL);
	return 0;
}

int send_response(int fd,char *msg)
{
	ssize_t nbytes;
	nbytes = send(fd,msg,strlen(msg),0);
	if(nbytes == -1)
		ERR("send_response");
	return nbytes;
}

int print_to_buf(char *buf,const char *format,char *str)
{
	int buf_end;
	buf_end = *(int *)pthread_getspecific(buf_end_key);
	sprintf(&buf[buf_end],format,str);
	buf_end = strlen(buf);
	if(buf_end>BUFSIZE)
		ERR("print_to_buf");
	return 0;
}

/* all_to_lowercase() 把buf内的字母转为小写 */
int all_to_lowercase(char *buf)
{
	int i,len;
	len = strlen(buf);
	
	for(i=0;i<len;i++)
		buf[i] = tolower(buf[i]);

	return i == len ? 0:-1;
}

int read_request(struct request *req,char *request_buf) 
{
	int i=0;
	char *c;
	c = request_buf;
	
	//跳过空格
	while(*c == ' ')
		c++;
	
	//读取请求方法
    while((*c != ' ') && (i < 8)){
		req->type[i] = *c;
		c++;
		i++;
	}
	req->type[i] = '\0';
	
	//读取URI
	while(*c != '/')
		c++;
	while(*c == '/')
		c++;
	if(*c == ' ')
		sprintf(req->filename,"%s/index.html",ROOT);
	else{
		sprintf(req->filename,"%s/",ROOT);
		i=strlen(ROOT)+1;
		while(*c != ' '){
			req->filename[i] = *c;
			c++;
			i++;
		}
		req->filename[i] = '\0';
	}

    return 0;
}

int handle_cgi(struct request *req)
{
	char output[12];
	sprintf(output," >%s/%d",CGITMP,(int)pthread_self());
	system(strcat(req->filename,output));
	execl("sed","-i","'s/\n/\r\n/g'","./o",(char *)NULL);
	sprintf(req->filename,"%s/%d",CGITMP,(int)pthread_self());
	sprintf(req->filetype,"cgi");

	return 0;
}