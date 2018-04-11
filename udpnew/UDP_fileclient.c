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
	int sockfd;
	char sbuff[80],filenamebuff[80];

	struct sockaddr_in serveraddr;


	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&serveraddr,sizeof(serveraddr));

	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(PORT);

	printf("Enter Filename : \n");
	scanf("%s",filenamebuff);

	int servlen=sizeof(serveraddr);

	sendto(sockfd,filenamebuff,sizeof(filenamebuff),0,(struct sockaddr *)&serveraddr,servlen);

	printf("Data: \n");

	while(recvfrom(sockfd,sbuff,80,0,(struct sockaddr *)&serveraddr,&servlen)!=NULL)
	{
		printf("%s",sbuff);
	}
	close(sockfd);
	return 0;

}