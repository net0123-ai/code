#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>

struct in_addr localInterface;
struct sockaddr_in groupSock; 
int sd;
char databuff[2024];

int main(){

    if((sd = socket(AF_INET,SOCK_DGRAM,0))<0){
        perror("error creating socket");
       	exit(1);
    }
      

    memset((char*) &groupSock , 0 , sizeof(groupSock));
    groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr("225.1.1.1");
    groupSock.sin_port = htons(5500);

    char loopback = 1;
    if(setsockopt(sd , IPPROTO_IP , IP_MULTICAST_LOOP , (char *)&loopback , sizeof(loopback))<0){
        perror("something wrong while setting the option");
        exit(1);
    }

    localInterface.s_addr = inet_addr("127.0.0.1");
    if(setsockopt(sd,IPPROTO_IP , IP_MULTICAST_IF , (char *)&localInterface , sizeof(localInterface))<0){
        perror("something worng while setting interface");
        exit(1);
    }

    int bufflen;

    for(;;){
        
        memset((char*) &databuff , 0 ,sizeof(databuff));
        printf("enter message");
        if(fgets(databuff,sizeof(databuff),stdin) == NULL){
            perror("error reading input");
            break;
        }
    
        if(sendto(sd , databuff , sizeof(databuff) , 0 , (struct sockaddr*)&groupSock , sizeof(groupSock))<0){
            printf("something wrong while sending message");
            exit(1);
        }

    }
}
