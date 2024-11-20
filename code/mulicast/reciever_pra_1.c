#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>


int sd;
char buffer[2024];
struct sockaddr_in local_addr;
struct ip_mreq group;


int main(){
	if((sd = socket(AF_INET,SOCK_DGRAM,0))<0){
	   perror("socket is not created");
	   exit(1);
	}
	
	int reuse = 1;
	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,(char *)&reuse,sizeof(reuse))<0){
		perror("error setting option");
		exit(1);
	}	
	
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(5000);
	
	if(bind(sd,(struct sockaddr*)&local_addr,sizeof(local_addr))<0){
		perror("error binding");
		exit(1);
	}
		
	group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
	group.imr_interface.s_addr = inet_addr("127.0.0.1");
	
	
	if(setsockopt(sd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&group,sizeof(group))<0){
		perror("error setting socket 2");
		exit(1);
	}
	
	for(;;){
		memset(buffer,0,sizeof(buffer));
		if(recvfrom(sd,buffer,sizeof(buffer)-1,0,NULL,0)<0){
			perror("error recieving");
			exit(1);
		}
		printf("%s",buffer);
	}
	return 0;
	
}

