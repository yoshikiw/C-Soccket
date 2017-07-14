#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void){

	struct sockaddr_in server;

	int socket_info_c;
	char buf[32];
	int n;

	if((socket_info_c = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("ERROR:socket-failed\n");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(8989);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(socket_info_c, (struct sockaddr *)&server, sizeof(server));

	memset(buf, 0, sizeof(buf));
	n = read(socket_info_c, buf, sizeof(buf));

	printf("%d-%s\n", n, buf);

	close(socket_info_c);

	return 0;
}