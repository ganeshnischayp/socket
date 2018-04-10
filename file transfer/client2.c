#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 1250
int main(int argc,char **argv)
{
    int client_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
     char filename[80],recv[80];
      
    // Creating socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
     bzero(&address,addrlen);
      
    // Forcefully attaching socket to the port 8080
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    inet_pton(AF_INET,argv[1],&address.sin_addr);
    connect(client_fd,(struct sockaddr*)& address,addrlen);
    printf("enter filename\n");
    scanf("%s",filename);
    write(client_fd,filename,80);
    while(read(client_fd,recv,80)!=0)
        printf("%s",recv);
    close(client_fd);
}