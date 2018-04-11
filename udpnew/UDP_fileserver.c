#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>        
#include <sys/socket.h>

#define PORT 10000

int main(int argc,char **argv)
{
	FILE *fp;
	char sbuff[80],filebuff[80];

	struct sockaddr_in serveraddr,clientaddr;

	int sockfd;

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(PORT);

	printf("Initialised.....\n");

	bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	printf("binded.....\n");

	int clientlength=sizeof(clientaddr);

	recvfrom(sockfd,filebuff,80,0,(struct sockaddr *)&clientaddr,&clientlength);

	printf("Receiving.....\n");

	fp=fopen(filebuff,"r");

	while(fgets(sbuff,80,fp)!=NULL)
	{
		sendto(sockfd,sbuff,80,0,(struct sockaddr *)&clientaddr,clientlength);
	}
	fclose(fp);
	close(sockfd);

	return 0;

}

