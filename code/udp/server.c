#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int sd;
char buffer[1024];
struct sockaddr_in ser_add , clie_add;

int main(){
    if((sd=socket(AF_INET,SOCK_DGRAM,0))<0){
    	perror("something wrong");
    }
    
    ser_add.sin_family = AF_INET;
    ser_add.sin_addr.s_addr = INADDR_ANY;
    ser_add.sin_port = htons(5000);
    
    if(bind(sd,(struct sockaddr *)&ser_add , sizeof(ser_add))<0){
        perror("something wrong");
    }
    
    
    int len = sizeof(clie_add);
    
    recvfrom(sd , buffer , sizeof(buffer),0,(struct sockaddr *)&clie_add , &len);
    
    printf("\n%s\n",buffer);
    return 0;   
}
