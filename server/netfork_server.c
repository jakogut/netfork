#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <netinet/in.h>

struct func_args { int a, b, c; };

int main(int argc, char *argv[])
{
	struct sockaddr_in serv_addr, cli_addr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset((char*)&serv_addr,0, sizeof(serv_addr));
	int portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	listen(sockfd,5);
	socklen_t clilen = sizeof(cli_addr);
	int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	char buffer[256];
	memset(buffer, 0, 256);

	read(newsockfd, buffer, 255);

	void* relocated_func = mmap(NULL, 4096, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	memcpy(relocated_func, buffer, 64); // FIXME

	void (*func_ptr)(void*) = relocated_func;

	struct func_args args = { 2, 3, 0 };
	func_ptr(&args);

	printf("Result is %i\n", args.c);

	close(newsockfd);
	close(sockfd);
	return 0;
}
