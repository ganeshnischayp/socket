#include <stdio.h>
#include<error.h>
#include<strings.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define PORT 10000

#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024
int main(int argc, char **argv)
{
    FILE *fp;
    int sock, new_socket, datalen;
    struct sockaddr_in server,client;
    int opt = 1;
    int addrlen = sizeof(struct sockaddr_in);
    int clienlen = sizeof(client);
    char data[MAX_DATA];
      
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failed");
        exit(-1);
    }
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr=INADDR_ANY;
    bzero(&server.sin_zero,8);
  
    if (bind(sock, (struct sockaddr *)&server, addrlen)<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sock,MAX_CLIENTS) < 0)
    {
        perror("listen");

        exit(EXIT_FAILURE);
    }
    while(1){ 

	    if ((new_socket = accept(sock, (struct sockaddr *)&client, &addrlen))<0)
	    {
	        perror("accept");
	        exit(EXIT_FAILURE);
	    }
	    printf("New client Connected from port no %d and IP %s\n", ntohs(client.sin_port), inet_ntoa(client.sin_addr));
	    datalen = 1;

	    while(datalen){
	    	datalen = recv(new_socket,data,MAX_DATA,0);
	    		if (datalen)
	    		{	
	    			send(new_socket,data,datalen,0);
	    			data[datalen] = '\0';
	    			printf("Sent mesg :%s\n", data);
	    		}
	    }		
	    printf("Client disconnected\n");
	    close(new_socket);
	}
	close(sock);
}