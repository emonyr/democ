

#include "global.h"

int main(int argc,const char *argv[])
{
	if (argc != 2){
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		return -1;
	}
	int client_fd = -1;
	struct sockaddr_in client_sock;
	socklen_t client_len;
	
	creat_server_fd(argv[1]);
	
wait:
	wait_for_connect(&client_fd,&client_sock,&client_len);

	switch(fork()) {
		case -1:
			/* error */
			ERR("fork");
			break;
		case 0:
			/* child, success */
			handle_request(client_fd);
			break;
		default:
			/* parent, success */
			close(client_fd);
			goto wait;
			break;
	}
	return 0;
}