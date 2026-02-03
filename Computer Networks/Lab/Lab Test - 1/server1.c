//
//  webclient_test.c
//  
//
//  Created by Pragati on 03/03/25.
//

// #include "webclient_test.h"
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXLINE 4096

// THIS IS ONLY THE ANSWER TO QUESTION 1
// SECOND answer IS NAMED server.c and client2.c

int main(int argc, char *argv[])
{
    int sockfd, portnum, n;
    struct sockaddr_in server_addr,peer_addr;
    socklen_t peer_addr_size;

    struct hostent *server;
    
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    int sendbytes;

    portnum = atoi(argv[1]);

    /* Create Server socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        fprintf(stderr, "ERROR opening socket\n");
        exit(1);
    }
    
    /* Fill in server address */
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnum);

    if (bind(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr)) == -1){
        fprintf(stderr,"can't bind\n");  
        return 0;
    }  
    if (listen(sockfd, 5) == -1){
        fprintf(stderr,"Can't listen\n");
        return 0;
    }
    
    peer_addr_size = sizeof(peer_addr);
    int newsockfd = accept(sockfd,(struct sockaddr *) &peer_addr, &peer_addr_size);
    
    if (newsockfd == -1){
        fprintf(stderr,"can't accept\n");
        return 0;
    }
    
    // Read response from client
    n = read(newsockfd,recvline,(MAXLINE-1));
    printf("%s\n",recvline);
    fflush(stdout);

    int len=strlen(recvline);
    int pos=0;
    if(len<13) sprintf(sendline,"Invalid version\n");
    else if(recvline[10]!='1' || recvline[11]!='.' || recvline[12]!='1') sprintf(sendline,"505 HTTP Version Not Supported\n");
    else{
        pos=1;
        sprintf(sendline, "200 OK\n");
    }
    memset(recvline, 0, MAXLINE);

    // connected prepare message for Client
     sendbytes = strlen(sendline);
    
    /* Write response */
    n = write(newsockfd,sendline,sendbytes);
    if (n < 0){
        fprintf(stderr, "ERROR writing to socket\n");
        exit(1);
    }

    if(!pos){
        printf("Closed due to varied HTTP versoin\n");
        close(sockfd);
        return 0;
    }

    return 0;
}