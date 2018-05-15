#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc , char *argv[]){
	int sock;
	char *ipadd;
	int Portnum;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buf[1024];
	int byte;
	unsigned int len;

	if(argc != 3){
		fprintf(stderr,"Uses : ./server IPaddress Portnumber\n");
		exit(1);
	}
	ipadd = argv[1];
	Portnum = atoi(argv[2]);
	
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	//server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_addr.s_addr = inet_addr(ipadd);
	//server.sin_port = htons(5000);
	server.sin_port = htons(Portnum);

	sock = socket(AF_INET,SOCK_DGRAM,0);
	bind(sock,(struct sockaddr *)&server,sizeof(server));

	while(recvfrom(sock,buf,1024,0,(struct sockaddr *)&client,&len) >= 0){
	//recvfrom(sock,buf,1024,0,(struct sockaddr *)&client,&len);
		printf("received %s",buf);
		int i = 0;
		char rebuf[1024];
		while(buf[i] != '\0'){
			rebuf[i] = (char)tolower(*buf);
			i++;
		}
		byte = strlen(rebuf)+1;
		sendto(sock,rebuf,byte,0,(struct sockaddr *)&client,sizeof(client));

	}
	close(sock);

	return 0;
}
