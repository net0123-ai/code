#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 22000
#define BUFFER_SIZE 100

int main() {
    int sockfd;
    struct sockaddr_in recvAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addrLen = sizeof(recvAddr);

    // Create a UDP socket for receiving datagrams
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        exit(1);
    }

    // Setup the address structure to bind the socket
    memset(&recvAddr, 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Listen on all interfaces
    recvAddr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(sockfd, (struct sockaddr *)&recvAddr, sizeof(recvAddr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    while (1) {
        int recvLen = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)&recvAddr, &addrLen);
        
        if (recvLen < 0) {
            perror("recvfrom failed");
            exit(1);
        }
        
	sendto(sockfd,buffer,BUFFER_SIZE-1,0,(struct sockaddr*)&recvAddr , addrLen);
    }

    return 0;
}
