#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int sd;
char buffer[2024];
struct sockaddr_in recver_addr;

int main(){
	if((sd=socket(AF_INET,SOCK_DGRAM,0))<0){
		perror("something wrong");
		exit(1);
	}
	
	recver_addr.sin_family = AF_INET;
	recver_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	recver_addr.sin_port = htons(5000);
	
	int broadcast = 1;
	if(setsockopt(sd,SOL_SOCKET,SO_BROADCAST,(char * )&broadcast,sizeof(broadcast))<0){
		perror("setting option");
		exit(1);
	}
	
	for(;;){
		memset(buffer,0,sizeof(buffer));
		printf("write message\n");
		if(fgets(buffer,sizeof(buffer),stdin) == NULL){
			perror("something wrong while input");
			exit(1);
		}
		if(sendto(sd,buffer,strlen(buffer),0,(struct sockaddr*)&recver_addr ,sizeof(recver_addr))<0){
			perror("something wrong while sending");
			exit(1);
		}
	}
	
	return 0;
}
