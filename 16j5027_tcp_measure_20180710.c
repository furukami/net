#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 1024*1024

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
	int recvbytes = 0;
	int rm;
	int conn;
	int byte;
	int bytesize;
	struct timeval start,end;
	double sec,usec;
	unsigned int len;

	if(argc != 4){
		fprintf(stderr,"Uses : ./client IPaddress Portnumver bytesize\n");
		exit(1);
	}

	ipadd = argv[1];
	Portnum = atoi(argv[2]);
	bytesize = atoi(argv[3]);

	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	//	printf("%s,",ipadd);
	server.sin_addr.s_addr = inet_addr(ipadd);
	//	printf("%d,",Portnum);
	server.sin_port = htons(Portnum);

	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0){
		ErrorMT("socket");
	}

	gettimeofday(&start,NULL);
	if((conn = connect(sock,(struct sockaddr *)&server,sizeof(server))) < 0){
		ErrorMT("connect");
	}
	gettimeofday(&end,NULL);
	sec = (double)(end.tv_sec-start.tv_sec);
	usec = (double)(end.tv_usec-start.tv_usec);
	printf("connect,%f\n",(sec*1000000)+usec);
	int string_point = 0;
	char buf[BUFSIZE];
	char rebuf[BUFSIZE];
	int recvbyte = 0;
	/*
	if((buf = (char *)malloc(bytesize)) == NULL){
		ErrorMT("malloc");
	}
	if((rebuf = (char *)malloc(bytesize)) == NULL){
		ErrorMT("malloc");
	}
	*/
	memset(buf,(int)'\0',sizeof(buf));
	memset(rebuf,(int)'\0',sizeof(buf));
	
	for(int i = 0; i < bytesize-1;i++){
		buf[i] = 'a';
	}
	byte = strlen(buf)+1;
		//sscanf(buf,"%s",buf);

	gettimeofday(&start,NULL);
	if(send(sock,buf,byte,0) <= 0){
		ErrorMT("sent");
	}
	gettimeofday(&end,NULL);
	sec = (double)(end.tv_sec-start.tv_sec);
	usec = (double)(end.tv_usec-start.tv_usec);
	printf("send,%f\n",(sec*1000000)+usec);

	gettimeofday(&start,NULL);
	while(1){
		rm = recv(sock,&rebuf[recvbyte],bytesize,0);
		recvbytes += rm;
		if(recvbytes == bytesize || rm == 0){
			break;
		}
	}
	gettimeofday(&end,NULL);
	sec = (double)(end.tv_sec-start.tv_sec);
	usec = (double)(end.tv_usec-start.tv_usec);
	//usec += sec*100000;
	printf("recv,%f\n",(sec*1000000)+usec);

	close(sock);
	//free(buf);
	//free(rebuf);

	return 0;
}
