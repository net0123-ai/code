#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

char buff[2024];
struct sockaddr_in localSock;
struct ip_mreq group;
int sd;

int main(int argc, char *argv[]) {
    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error creating socket");
        exit(1);
    }

    int reuse = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) {
        perror("Error setting SO_REUSEADDR");
        close(sd);
        exit(1);
    }

    memset((char *)&localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_addr.s_addr = INADDR_ANY;
    localSock.sin_port = htons(5500);

    if (bind(sd, (struct sockaddr *)&localSock, sizeof(localSock)) < 0) {
        perror("Error binding socket");
        close(sd);
        exit(1);
    }

    group.imr_multiaddr.s_addr = inet_addr("225.1.1.1");
    group.imr_interface.s_addr = inet_addr("127.0.0.1");

    if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0) {
        perror("Error adding multicast group");
        close(sd);
        exit(1);
    }

    for(;;) {
        memset(buff, 0, sizeof(buff));
        if (recvfrom(sd, buff, sizeof(buff)-1 , 0, NULL,0) < 0) {
            perror("reading datagram message");
            close(sd);
            exit(1);
        }
        printf("%s\n", buff);
    }

    return 0;
}
