#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<arpa/inet.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include<errno.h>
#include<stdlib.h>



int main(int argc, char  **argv)
{
	int sock,cli;
	struct sockaddr_in server,clientDetail;
	unsigned int len;
	char mesg[] = "Hello man\n";
	int sentconf;
	if ((sock = socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		perror("There is some issue in creating sockets");
		exit(-1);
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero,8);
	len = sizeof(struct sockaddr_in);
	if ((bind(sock,(struct sockaddr *)&server,len)) == -1)
	{
		perror("Error in binding");
		exit(-1);
	}
	if ((listen(sock,5)) == -1)
	{
		perror("error in listening");
		exit(-1);
	}
	while(1){
		if ((cli = accept(sock,(struct sockaddr *)&clientDetail,&len)) == -1)
		{
			perror("error in acceptint");
			exit(-1);
		}
		sentconf = send(cli,mesg,strlen(mesg),0);
		printf("sending %d bytes to clientDetail: %s\n",sentconf,inet_ntoa(clientDetail.sin_addr));
		close(cli);
	}
	return 0;
}