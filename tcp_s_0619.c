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
	int rm;
	int byte;
	int bytesize;
	int i;
	unsigned int len;
	int s;

	if(argc != 4){
		fprintf(stderr,"Uses : ./server IPaddress Portnumber bytesize\n");
		exit(1);
	}
	ipadd = argv[1];
	Portnum = atoi(argv[2]);
	bytesize = atoi(argv[3]);


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
		while(1){
			char* buf;
			char* rebuf;
			if((buf = (char *)malloc(bytesize)) == NULL){
				ErrorMT("malloc");
			}	
			if((memset(buf,(int)'\0',sizeof(rebuf))) == NULL){
				ErrorMT("memset");
			}
			while(1){
				rm = recv(s,buf,bytesize,0);
				printf("%d \n",atoi(buf));		
			char *p = buf;
			if((rebuf = (char *)malloc(bytesize)) == NULL){
				ErrorMT("malloc");
			}
			if((memset(rebuf,(int)'\0',sizeof(rebuf))) == NULL){
				ErrorMT("memset");
			}
			byte = strlen(rebuf)+1;
			//		fprintf(stdout,"%s",rebuf);
			if(send(s,rebuf,byte,0) <= 0){
				break;
				ErrorMT("send");
			}
			printf("%s\n",rebuf);
		}

	}
	if(close(sock) < 0){
		ErrorMT("close");
	}

	return 0;
}
