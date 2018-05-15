#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc,char *argv[]){
	int sock;
	char *ipadd;
	int Portnum;
	struct sockaddr_in server;
	struct sockaddr_in client;
//	char buf[1024] = "hoge";
	char buf[1024];
	char rebuf[1024];
	int byte;
	unsigned int len;

	if(argc != 3){
		fprintf(stderr,"Uses : ./client IPaddress Portnumver\n");
		exit(1);
	}

	ipadd = argv[1];
	Portnum = atoi(argv[2]);
	fprintf(stdout,"What do you sent word?\n");
	fgets(buf,sizeof(buf),stdin);
	
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
//	printf("%s,",ipadd);
	server.sin_addr.s_addr = inet_addr(ipadd);
//	printf("%d,",Portnum);
	server.sin_port = htons(Portnum);
	byte = strlen(buf)+1;

	sock = socket(AF_INET,SOCK_DGRAM,0);
	sendto(sock,buf,byte,0,(struct sockaddr *)&server,sizeof(server));
	recvfrom(sock,rebuf,1024,0,(struct sockaddr *)&client,&len);
	printf("received %s",rebuf);
	close(sock);

	return 0;
}
