#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main()
{
	int s;
	char *node = "www.baidu.com";
	struct addrinfo hint;
	struct addrinfo *res;
	struct in_addr addr;

	memset(&hint,0,sizeof(struct addrinfo));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_flags = 0;
	hint.ai_protocol = 0;

	s = getaddrinfo(node,NULL,&hint,&res);
	if (s != 0)
	{
		perror("getaddrinfo");
		exit(EXIT_FAILURE);
	}
	addr.s_addr = (uint64_t)(res->ai_addr);
	printf("address is :%s\n",inet_ntoa(addr));
	return 0;

}

