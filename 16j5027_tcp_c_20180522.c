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
	int string_point = 0;
	struct sockaddr_in server;
	struct sockaddr_in client;
//	char buf[1024] = "hoge";
	char buf[1024];
	char rebuf[1024];
	char catch[1024];
	int rm;
	int byte;
	unsigned int len;

	if(argc != 3){
		fprintf(stderr,"Uses : ./client IPaddress Portnumver\n");
		exit(1);
	}

	ipadd = argv[1];
	Portnum = atoi(argv[2]);
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
	//sscanf(buf,"%s",buf);
	
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
//	printf("%s,",ipadd);
	server.sin_addr.s_addr = inet_addr(ipadd);
//	printf("%d,",Portnum);
	server.sin_port = htons(Portnum);
	byte = strlen(buf)+1;

	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
		ErrorMT("socket");
	}
	if(connect(sock,(struct sockaddr *)&server,sizeof(server)) < 0){
		ErrorMT("connect");
	}


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
/*
16j5027@lin3441:~/Cnetwork$ ./client 160.194.128.163 5000
What do you sent word?
HOGEHOGE
received hogehoge

16j5027@lin3441:~/Cnetwork$
*/
