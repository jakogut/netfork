#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

struct func_args { int a, b, c; };

void func(void* generic_arg)
{
	struct func_args* args = (struct func_args*)generic_arg;
	args->c = args->a + args->b;
}

int main(int argc, char *argv[])
{
	int portno = atoi(argv[2]);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct hostent* server = gethostbyname(argv[1]);

	struct sockaddr_in serv_addr;
	memset((char*)&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	memcpy((char*)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));

	char buffer[256];
	memset(buffer, 0, 256);

	memcpy(buffer, (void*)&func, ((long)&main - (long)&func));
	write(sockfd,buffer,strlen(buffer));

	close(sockfd);
	return 0;
}
