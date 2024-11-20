#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

int sd , li;
struct sockaddr_in serv_addr , cli_addr;
char buffer[1024];

int main(){ 	
 	if((sd = socket(AF_INET,SOCK_STREAM,0))<0){
 	   perror("something wrong");
 	}
 	
 	serv_addr.sin_family = AF_INET;
 	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 	serv_addr.sin_port = htons(5000);
 	
 	if(bind(sd,(struct sockaddr*)&serv_addr , sizeof(serv_addr))<0){
 	   perror("something wrong bind");
 	}
 	
 	if(listen(sd,3)<0){
           perror("something wrong listen");
 	}
 	
 	int len = sizeof(cli_addr);
 	if((li = accept(sd,(struct sockaddr*)&cli_addr,&len))<0){
 	   perror("something wrong accept");
 	}
 
 	for(;;){
 	
	 	read(li,buffer,sizeof(buffer));
	 	printf("messgae from client: ");
	 	puts(buffer);
	 	memset(buffer,0,sizeof(buffer));
	 	fgets(buffer,sizeof(buffer),stdin);
	 	write(li,buffer,sizeof(buffer));

 	}
 	
 	return 0;
 	
 }
