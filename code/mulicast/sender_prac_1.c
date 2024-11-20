#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>


int sd;
char buffer[2024];
struct sockaddr_in group_sock;
struct in_addr interface;


int main(){
	if((sd = socket(AF_INET,SOCK_DGRAM,0))<0){
	   perror("socket is not created");
	   exit(1);
	}
	
	group_sock.sin_addr.s_addr = inet_addr("225.1.1.1");
	group_sock.sin_family = AF_INET;
	group_sock.sin_port = htons(5000);
	
	
	int loopback = 0;
	if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_LOOP,(char *)&loopback,sizeof(loopback))<0){
		perror("error setting option");
		exit(1);
	}	
	
	
	interface.s_addr = inet_addr("127.0.0.1");
	if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_IF,(char *)&interface,sizeof(interface))<0){
		perror("error setting socket 2");
		exit(1);
	}
	
	for(;;){
		printf("write your message \n");
		if(fgets(buffer,sizeof(buffer),stdin)==NULL){
		       perror("error input");
		       exit(1);
		}	
	
		if(sendto(sd,buffer,sizeof(buffer),0,(struct sockaddr*)&group_sock,sizeof(group_sock))<0){
			perror("error sending");
			exit(1);
		}
		memset(buffer,0,sizeof(buffer));
	}
	return 0;
	
}

