#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int sd;
char buffer[2024];
struct sockaddr_in recver_addr , send_addr;

int main(){
	if((sd=socket(AF_INET,SOCK_DGRAM,0))<0){
		perror("something wrong");
		exit(1);
	}
	
	recver_addr.sin_family = AF_INET;
	recver_addr.sin_addr.s_addr = INADDR_ANY;
	recver_addr.sin_port = htons(5000);

	int resuse = 1;
	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,(char *)&resuse,sizeof(resuse))<0){
		perror("something wrong in setting the option");
	}

		
	if(bind(sd,(struct sockaddr* )&recver_addr,sizeof(recver_addr))<0){
		perror("error binding");
		exit(1);
	}
	
	for(;;){
		memset(buffer,0,sizeof(buffer));
		int len = sizeof(send_addr);
		if(recvfrom(sd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&send_addr,&len)<0){
			perror("something wrong while sending");
			exit(1);
		}
		printf("%s\n",buffer);
	}
	
	return 0;
}
