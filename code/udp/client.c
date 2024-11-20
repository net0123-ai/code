#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int sd;
char buffer[1024] = "hello";
struct sockaddr_in ser_add;

int main(){
	if((sd=socket(AF_INET,SOCK_DGRAM,0))<0){
		perror("something worong creating socket");
		exit(1);
	}
	
	ser_add.sin_family = AF_INET;
	ser_add.sin_addr.s_addr = INADDR_ANY;
	ser_add.sin_port = htons(5000);
	
	int len = sizeof(ser_add);
	sendto(sd,buffer,strlen(buffer),0,(struct sockaddr *)&ser_add,len);
	printf("\nSent\n");
	return 0;
}
	
