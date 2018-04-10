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
#define BUFFER 1024


int main(int argc,char **argv)
{
    int sock;
    struct sockaddr_in remote_server;
    char input[BUFFER], output[BUFFER];
    int len;
      

    if ((sock= socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    remote_server.sin_family = AF_INET;
    remote_server.sin_port = htons(atoi(argv[2]));
    remote_server.sin_addr.s_addr = inet_addr(argv[1]);
    bzero(&remote_server.sin_zero, 0);
    
    if((connect(sock, (struct sockaddr *)&remote_server, sizeof(struct sockaddr_in)))==ERROR)
    {
        perror("connect");
        exit(-1);
    }  
    while(1)
    {
        fgets(input, BUFFER, stdin);
        send(sock, input, strlen(input), 0);

        len= recv(sock, output, BUFFER, 0);
        output[len] = '\0';
        printf("%s\n",output);
    }
    close(sock);
   
}