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

// THIS IS ONYL THE ANSWER TO QUESTION 1

int main(int argc, char *argv[])
{
    int sockfd, portnum, n;
    struct sockaddr_in server_addr;
    struct hostent *server;
    
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    int sendbytes;
    
    if (argc < 3) {
       fprintf(stderr,"usage %s <server-ip-addr> <server-port>\n", argv[0]);
       exit(0);
    }

    portnum = atoi(argv[2]);

    /* Create client socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
      {
    fprintf(stderr, "ERROR opening socket\n");
    exit(1);
      }
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    /* Fill in server address */
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
  
    server_addr.sin_port = htons(portnum);

    /* Connect to server */
    if (connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
      {
    fprintf(stderr, "ERROR connecting\n");
    exit(1);
      }
    printf("Connected to server\n");
    
    // connected prepare message for web server
    sprintf(sendline, "GET /HTTP/1.0\nConnections: keep-alive\n\n");
    sendbytes = strlen(sendline);
    /* Write to server */
    n = write(sockfd,sendline,sendbytes);
    if (n < 0)
      {
        fprintf(stderr, "ERROR writing to socket\n");
        exit(1);
      }
    
    // read server response
    n = read(sockfd,recvline,(MAXLINE-1));
    printf("%s",recvline);
    memset(recvline, 0, MAXLINE);
    if (n < 0){
        fprintf(stderr, "ERROR reading from socket\n");
        exit(1);
    }

    return 0;
}