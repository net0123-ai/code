#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>


int sd , newsd;
struct sockaddr_in server_addr , client_addr;
char buffer[2024];

int main(){
	
	if((sd=socket(AF_INET,SOCK_STREAM,0))<0){
		perror("socket");
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(5000);
	
	if(bind(sd,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		perror("binding");
	}
	
	if(listen(sd , 3)<0){
		perror("listen");
	}
	
	int len = sizeof(server_addr);
	if((newsd = accept(sd,(struct sockaddr*)&client_addr , &len))<0){
		perror("accept");
		exit(1);
	}
	
	read(newsd,buffer,sizeof(buffer));
 	printf("messgae is : ");
 	printf("%s",buffer);
				
	return 0;
}
