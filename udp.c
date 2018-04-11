UDP


// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define PORT     8080
#define MAXLINE 1024
 
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
     
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
     
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
     
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
     
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
     
    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    printf("Hello message sent.\n"); 
     
    return 0;
}





// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
 
#define PORT     8080
#define MAXLINE 1024
 
// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from client";
    struct sockaddr_in     servaddr;
 
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    memset(&servaddr, 0, sizeof(servaddr));
     
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
     
    int n, len;
     
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Hello message sent.\n");
         
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
 
    close(sockfd);
    return 0;
}



#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#define PORT 8080
int main(int argc, char **argv)
{
	char buffer[1024];
	struct sockaddr_in servAddr;
	int sockfd=socket(PF_INET,SOCK_DGRAM,0);
	servAddr.sin_family=AF_INET;
	servAddr.sin_port=htons(PORT);
	socklen_t servSize=sizeof(servAddr);
	printf("Enter a sentence: \n");
	fgets(buffer,1024,stdin);
	int len=strlen(buffer)+1;
	sendto(sockfd,buffer,len,0,(struct sockaddr *)&servAddr,servSize);

}



#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define PORT 8080
int main()
{
	struct sockaddr_in serv_addr,cli_addr;
	char buffer[1024];
	socklen_t addr_size;
	int sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0)
		perror("Error creating socket!");
	memset(&serv_addr, '\0', sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);
	bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	addr_size=sizeof(cli_addr);
	int n=recvfrom(sockfd,buffer,1024,0,(struct sockaddr*)&cli_addr,&addr_size);
	printf("%s\n",buffer );
}
