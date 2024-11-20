#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int sd;
struct sockaddr_in ser_addr;
char buffer[1024]="hello";

int main(){
    if((sd = socket(AF_INET,SOCK_STREAM,0))<0){
    	perror("something wrong");	
    }
    
    ser_addr.sin_family = AF_INET; 
    ser_addr.sin_port = htons(5000);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(sd, (struct sockaddr*)&ser_addr,sizeof(ser_addr)) < 0) {
        printf("\n Error : Connect Failed \n");
    }
    
    write(sd,buffer,strlen(buffer));
    return 0;
    
}
