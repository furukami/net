#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFSIZE 1024*1024

void ErrorMT(char *str){
	fprintf(stderr,"Faild to %s",str);
	exit(1);
}

int main(int argc,char *argv[]){
	int sock;
	char *ipadd;
	int Portnum;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int bytesize;
//	char buf[1024] = "hoge";
	char *buf;
	char *rebuf;
	int rm;
	int byte;
	unsigned int len;
	int p = 0;

	struct timeval start,end;
	double sec,usec;
	if(argc != 4){
		fprintf(stderr,"Uses : ./client IPaddress Portnumver Bytesize\n");
		exit(1);
	}

	ipadd = argv[1];
	Portnum = atoi(argv[2]);
	bytesize = atoi(argv[3]);
	/*
	fprintf(stdout,"What do you sent word?\n");
	if(fgets(buf,sizeof(buf),stdin) == NULL){
		ErrorMT("input");
		//fprintf(stderr,"Faild to input\n");
	}
	*/

	if((buf = (char *)malloc(bytesize)) == NULL){
		ErrorMT("malloc");
	}
	if((rebuf = (char *)malloc(bytesize)) == NULL){
		ErrorMT("malloc");
	}

	memset(buf,(int)'\0',sizeof(buf));	
	memset(rebuf,(int)'\0',sizeof(buf));	
	for(int i = 0;i < bytesize -1;i++){
		buf[i] = 'a';
	};
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
//	printf("%s,",ipadd);
	server.sin_addr.s_addr = inet_addr(ipadd);
//	printf("%d,",Portnum);
	server.sin_port = htons(Portnum);
	byte = strlen(buf)+1;
	
	if((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0){
		ErrorMT("socket");
	}
	gettimeofday(&start,NULL);
	if(sendto(sock,buf,byte,0,(struct sockaddr *)&server,sizeof(server)) < 0){
		ErrorMT("sent");
	}
	gettimeofday(&end,NULL);
	sec = (double)(end.tv_sec-start.tv_sec);
	usec = (double)(end.tv_usec-start.tv_usec);


	gettimeofday(&start,NULL);
	if((rm = recvfrom(sock,rebuf,bytesize,0,(struct sockaddr *)&client,&len)) < 0){
		ErrorMT("reception");
	}
	gettimeofday(&end,NULL);
	sec = (double)(end.tv_sec-start.tv_sec);
	usec = (double)(end.tv_usec-start.tv_usec);
	printf("recv,%f\n",(sec*1000000)+usec);

//	printf("received %s\n",rebuf);
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
