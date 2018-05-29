#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include<sys/socket.h>
#include<netinet/in.h>

void ErrorMT(char *str){
	fprintf(stderr,"Falild to %s\n",str);
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
	int s;

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

	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
		ErrorMT("socket");
	}
	if(bind(sock,(struct sockaddr *)&server,sizeof(server)) < 0){
		ErrorMT("bind");
	}
	if(listen(sock,5) < 0){
		ErrorMT("listen");
	}
	while(1){
	if((s = accept(sock,(struct sockaddr *)&client,&len)) < 0){
		ErrorMT("accept");
	}	

	if((rm = recv(s,buf,1024,0)) <= 0){
		ErrorMT("recv");
	}
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
	if(send(s,rebuf,byte,0) < 0){
		ErrorMT("send");
	}

	}
	if(close(sock) < 0){
		ErrorMT("close");
	}

	return 0;
}
