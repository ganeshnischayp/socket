#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#define PORT 1250
int main()
{   FILE *fp;
    int sock, new_socket, valread;
    struct sockaddr_in server,clientDetails ;
    int opt = 1;
    int addrlen = sizeof(server);
    int clienlen = sizeof(clientDetails);
    char f[80],s[80];
      
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket failed");
        exit(-1);
    }
      bzero(&server,addrlen);
    // Forcefully attaching socket to the port 8080
    server.sin_family = AF_INET;
    //server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8080
    if (bind(sock, (struct sockaddr *)&server, 
                                 sizeof(server))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sock,1) < 0)
    {
        perror("listen");

        exit(EXIT_FAILURE);
    }
    
    if ((new_socket = accept(sock, (struct sockaddr *)&clientDetails, &clienlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    read(new_socket,f,80);
    fp=fopen(f,"r");
    printf("filename %s\n",f);
    while(fgets(s,80,fp)!=NULL)
        write(new_socket,s,sizeof(s));
    close(new_socket);
    fclose(fp);
}