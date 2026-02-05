#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

#define BUFFER_SIZE 256

int sockfd; 

void error(const char *msg) 
{
    perror(msg);
    exit(1);
}
void *writeClient(void *arg) 
{
    char buffer[BUFFER_SIZE];

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE - 1, stdin);
        ssize_t n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) error("ERROR writing to socket");
        if (strncmp(buffer, "exit", 4) == 0) 
        {
            printf("Disconnecting...\n");
            close(sockfd);
            exit(0);
        }
    }
}

void *readClient(void *arg) 
{
    char buffer[BUFFER_SIZE];

    while (1) {
        bzero(buffer, BUFFER_SIZE);
        ssize_t n = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (n < 0) error("ERROR reading from socket");
        if (n == 0) {
            printf("Server closed the connection.\n");
            close(sockfd);
            exit(0);
        }

        printf("\nServer: %s\n", buffer);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    int portno = atoi(argv[2]);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) 
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(1);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("Connected to server. Type 'exit' to disconnect.\n");
    pthread_t writeThread, readThread;
    pthread_create(&writeThread, NULL, writeClient, NULL);
    pthread_create(&readThread, NULL, readClient, NULL);
    pthread_join(writeThread, NULL);
    pthread_join(readThread, NULL);

    close(sockfd);
    return 0;
}