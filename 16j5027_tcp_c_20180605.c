#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

void ErrorMT(char *str){
	fprintf(stderr,"Faild to %s\n",str);
	exit(1);
}

int main(int argc,char *argv[]){
	int sock;
	char *ipadd;
	int Portnum;
	struct sockaddr_in server;
	struct sockaddr_in client;
	//	char buf[1024] = "hoge";
	int rm;
	int conn;
	int byte;
	unsigned int len;

	if(argc != 3){
		fprintf(stderr,"Uses : ./client IPaddress Portnumver\n");
		exit(1);
	}

	ipadd = argv[1];
	Portnum = atoi(argv[2]);

	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	//	printf("%s,",ipadd);
	server.sin_addr.s_addr = inet_addr(ipadd);
	//	printf("%d,",Portnum);
	server.sin_port = htons(Portnum);

	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
		ErrorMT("socket");
	}
	if((conn = connect(sock,(struct sockaddr *)&server,sizeof(server))) < 0){
		ErrorMT("connect");
	}

	int string_point = 0;
	char buf[1024];
	char rebuf[1024];
	char catch[1024];
	memset(buf,(int)'\0',sizeof(buf));
	memset(rebuf,(int)'\0',sizeof(buf));
	memset(catch,(int)'\0',sizeof(buf));

	fprintf(stdout,"What do you sent word?\n");
	if(fgets(catch,sizeof(buf),stdin) == NULL){
		ErrorMT("input");
			//fprintf(stderr,"Faild to input\n");
	}
	while(catch[string_point] != '\0'){
		if(catch[string_point] == '\n'){
			buf[string_point] = '\0';
		}else{
			buf[string_point] = catch[string_point];
		}
		string_point++;
	}
	byte = strlen(buf)+1;
		//sscanf(buf,"%s",buf);

	if(send(sock,buf,byte,0) < 0){
		ErrorMT("sent");
	}
	if((rm = recv(sock,rebuf,1024,0)) < 0){
		ErrorMT("reception");
	}

	printf("received %s\n",rebuf);
	close(sock);

	return 0;
}
