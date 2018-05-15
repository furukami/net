#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include<sys/socket.h>
#include<netinet/in.h>

void ErrorMT(char *str){
	fprintf(stderr,"Falild to %s",str);
	exit(1);
}

int main(int argc , char *argv[]){
	int sock;
	char *ipadd;
	int Portnum;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buf[1024];
	char rebuf[1024];
	int rm;
	int byte;
	int i;
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

	if((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0){
		ErrorMT("socket");
	}
	if(bind(sock,(struct sockaddr *)&server,sizeof(server)) < 0){
		ErrorMT("bind");
	}

	while(rm = recvfrom(sock,buf,1024,0,(struct sockaddr *)&client,&len) >= 0){
	//recvfrom(sock,buf,1024,0,(struct sockaddr *)&client,&len);
		printf("received %s\n",buf);
		i = 0;
		char *p = buf;
		while(*p != '\0'){
			rebuf[i] = (char)tolower(*p);
			i++;
			p++;
		}
		byte = strlen(rebuf)+1;
//		fprintf(stdout,"%s",rebuf);
		if(sendto(sock,rebuf,byte,0,(struct sockaddr *)&client,sizeof(client)) < 0){
			fprintf(stderr,"Not send\n");
		}

	}
	close(sock);

	return 0;
}
