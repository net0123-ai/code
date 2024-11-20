#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 22000 // Port number for eco server
int main() {
    char buffer[100];
    int sockfd , len;
    struct sockaddr_in broadcastAddr;
    int broadcastPermission = 1;  // Allow broadcast

    // Create socket for sending datagrams
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        exit(1);
    }

    // Setup the broadcast address structure
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    broadcastAddr.sin_port = htons(PORT);

    // Send the message
    while(1){
    	fgets(buffer , sizeof(buffer),stdin);
      	if (sendto(sockfd,buffer,sizeof(buffer),0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) < 0) {
		perror("sendto failed");
		exit(1);
    	}	
    	printf("sent\n");
    	len = sizeof(broadcastAddr);
    	recvfrom(sockfd , buffer , sizeof(buffer),0,(struct sockaddr *)&broadcastAddr,&len);
    	puts(buffer);
	}
	
    return 0;
}
