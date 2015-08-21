/*
 * protocal.c 
 * �ṩhttpЭ����صĺ���
 */

#include "global.h"

int buf_end;

/* dispatch() �����������ͷ������� */
int dispatch(int fd)
{	
	if(all_to_lowercase(request_buf) == -1)
		ERR("all_to_lowercase");
	
	printf("%s\n\n",request_buf);
    //��request_buf��ȡ��request�ṹ��
	struct request *s;
	s = (struct request *)malloc(sizeof(struct request));
	memset(s,0,sizeof(struct request));
	if(read_request(s) != 0){
		send_response(fd,"HTTP/1.1 400 Bad Request\r\n");
		free(s);
		close(fd);
		ERR("read_request");
	}
	
	//ͨ���ṹ���typeʶ�����󷽷�
	memset(response_buf,0,BUFSIZE);
	if((strcmp(s->type,"get") == 0) || (strcmp(s->type,"head") == 0))
		response_get(s);
    else if(strcmp(s->type,"post") == 0)
		response_post(s);
    else if(strcmp(s->type,"put") == 0)
		response_put(s);
	else if(strcmp(s->type,"delete") == 0)
		response_delete(s);
    else
		print_to_buf(response_buf,"HTTP/1.1 400 Bad Request\r\n",NULL);
	
	printf("%s\n\n",response_buf);
	send_response(fd,response_buf);
	free(s);
	close(fd);

	return 0;
}

int response_get(struct request *s)
{
	int resoucefd,nbytes;
	char filesize[32];
	struct stat sb;
	
	current_time();
	printf("\nProcessing GET request: pid = %d\n",getpid());
	printf("+++++++s->filename: %s\n",s->filename);
	
	stat(s->filename,&sb);
	if(sb.st_mode & S_IXUSR)
		handle_cgi(s->filename);
	
	resoucefd = open(s->filename,O_RDONLY,0666);
	if(resoucefd == -1){
		print_to_buf(response_buf,"HTTP/1.1 400 Bad Request\r\n",NULL);
		perror("open");
		return -1;
	}
	sprintf(filesize,"%d",(int)lseek(resoucefd,0,SEEK_END));

	buf_end = 0;
	print_to_buf(response_buf,"HTTP/1.1 200 OK\r\n",NULL);
	print_to_buf(response_buf,"Server: jyserver\r\n",NULL);
	print_to_buf(response_buf,"Date: %s\r\n",GMTtime);
	print_to_buf(response_buf,"Connection: Closed\r\n",NULL);
	print_to_buf(response_buf,"Content-Length: %s\r\n",filesize);
	print_to_buf(response_buf,"Content-Type: text/html\r\n",NULL);
	print_to_buf(response_buf,"Cache-Control: no-cache\r\n",NULL);
	print_to_buf(response_buf,"\r\n",NULL);
	if(strcmp(s->type,"head") == 0)
		return 0;
	
	lseek(resoucefd,0,SEEK_SET);
	while(nbytes != 0){
		nbytes = read(resoucefd,&response_buf[buf_end],1024);
		buf_end = buf_end + nbytes;
	}
	unlink(s->filename);
	close(resoucefd);
	
	return 0;
}

int response_post(struct request *s)
{
	print_to_buf(response_buf,"HTTP/1.1 400 Bad Request\r\n",NULL);
	return 0;
}

int response_put(struct request *s)
{
	print_to_buf(response_buf,"HTTP/1.1 400 Bad Request\r\n",NULL);
	return 0;
}

int response_delete(struct request *s)
{
	print_to_buf(response_buf,"HTTP/1.1 400 Bad Request\r\n",NULL);
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
	sprintf(&buf[buf_end],format,str);
	buf_end = strlen(buf);
	if(buf_end>BUFSIZE)
		ERR("print_to_buf");
	return 0;
}

/* all_to_lowercase() ��buf�ڵ���ĸתΪСд */
int all_to_lowercase(char *buf)
{
	int i,len;
	len = strlen(buf);
	
	for(i=0;i<len;i++)
		buf[i] = tolower(buf[i]);

	return i == len ? 0:-1;
}

int read_request(struct request *s) 
{
	int i=0;
	char *c;
	c = request_buf;
	
	//�����ո�
	while(*c == ' ')
		c++;
	
	//��ȡ���󷽷�
    while((*c != ' ') && (i < 8)){
		s->type[i] = *c;
		c++;
		i++;
	}
	s->type[i] = '\0';
	
	//��ȡURI
	while(*c != '/')
		c++;
	while(*c == '/')
		c++;
	if(*c == ' ')
		sprintf(s->filename,"%s/index.html",ROOT);
	else{
		sprintf(s->filename,"%s/",ROOT);
		i=strlen(ROOT)+1;
		while(*c != ' '){
			s->filename[i] = *c;
			c++;
			i++;
		}
		s->filename[i] = '\0';
	}

    return 0;
}

int handle_cgi(char *filename)
{
	char output[12];
	sprintf(output," >%d",getpid());
	system(strcat(filename,output));
	execl("sed","-i","'s/\n/\r\n/g'","./o",(char *)NULL);
	sprintf(filename,"./%d",getpid());
	
	return 0;
}









