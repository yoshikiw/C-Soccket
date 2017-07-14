#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void){

	struct sockaddr_in addr;
	struct sockaddr_in client;

	int socket_info;
	int len;
	int sock;

	if((socket_info = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("ERROR:socket-failed\n");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8989);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(socket_info, (struct sockaddr *)&addr, sizeof(addr));

	listen(socket_info, 5);

	while(1){

		len = sizeof(client);
		sock = accept(socket_info, (struct sockaddr *)&client, &len);

		printf("AcceptedConectionFrom:%s\n", inet_ntoa(client.sin_addr));
		printf("port:%d\n", ntohs(client.sin_port));

		write(sock, "Connected", 9);

		close(sock);

	}

	close(socket_info);

	return 0;
}