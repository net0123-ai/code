#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int sd;
char buffer[1024];
struct sockaddr_in se_addr,re_addr;

int main(){
    
    if((sd = socket(AF_INET,SOCK_DGRAM,0))<0){
    	perror("error creating socket");
    }
    
    re_addr.sin_family = AF_INET;
    re_addr.sin_addr.s_addr = INADDR_ANY;
    re_addr.sin_port = htons(5000);
    
    if(bind(sd,(struct sockaddr *)&re_addr,sizeof(re_addr))<0){
    	perror("error binding socket");
    }
    
    int len = sizeof(se_addr);
    recvfrom(sd,buffer,sizeof(buffer)-1,0,(struct sockaddr*)&se_addr,&len);
    printf("\n%s\n",buffer);
    
    return 0;
       
}
