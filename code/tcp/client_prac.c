#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>


int sd;
struct sockaddr_in server_addr;
char buffer[2024]="hello";

int main(){

	if((sd=socket(AF_INET,SOCK_STREAM,0))<0){
		perror("socket");
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(5000);
	
	if(connect(sd,(struct sockaddr*)&server_addr , sizeof(server_addr))<0){
		perror("connect");
	}
	
	write(sd , buffer  , strlen(buffer));
	
	return 0;
}
