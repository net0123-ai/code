#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int sd;
char buffer[1024] = "hello world";
struct sockaddr_in se_addr;

int main(){
    if((sd=socket(AF_INET,SOCK_DGRAM,0))<0){
    	perror("error while creating socket");
    	exit(1);   	   
    }
    
    int broad = 1;
    if(setsockopt(sd,SOL_SOCKET,SO_BROADCAST,&broad,sizeof(broad))<0){
    	perror("error while setting");
    }
    
    se_addr.sin_family = AF_INET;
    se_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    se_addr.sin_port = htons(5000);
    
        
    sendto(sd,buffer,sizeof(buffer),0,(struct sockaddr*)&se_addr , sizeof(se_addr));
    
    return 0;
    
}


