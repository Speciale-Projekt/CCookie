//
// Created by larsb on 18-05-2022.
//

#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

int main() {

    struct sockaddr_in serverAddr, clientAddr;
    int                listenAddr   =  7331;
    char              *listenDomain = "127.0.0.1";
    int                sockfd       = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(1);
    }
    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family      = AF_INET;
    serverAddr.sin_port        = htons(listenAddr);
    serverAddr.sin_addr.s_addr = inet_addr(listenDomain);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind \n");
        exit(1);
    }

    while(1){
        char      buffer[1024];
        socklen_t clilen = sizeof(clientAddr);
        ssize_t   n      = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &clilen);

        if (n > 0) {
            printf("%s",buffer);
            sleep(0.01);
            exit(1);
        }

    }
}