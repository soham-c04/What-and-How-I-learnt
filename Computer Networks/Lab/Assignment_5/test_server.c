#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}
int active_clients=0;
#define MAX_CLIENT 10
// At most 10 clients can be handled can be increased more will result in discrepancies
char Client_name[MAX_CLIENT][20];
int sock[MAX_CLIENT];
void *Clients(int newsockfd){
    while(1){
        printf("%d newsock\n",newsockfd);
        char buffer[256];
        bzero(buffer,256);
        int n = read(newsockfd,buffer,255);
        int len=strlen(buffer);
        int start=0,name_end;
        for(int i=0;i<len;i++){
            if(buffer[i]==':'){
                start=i;
                name_end=i;
            }
            else if(start && (i<len-1) && buffer[i]!=' ') start=0;
        }
        if (n < 0) error("ERROR reading from socket");
        int exit_=(buffer[name_end+2]=='e' && buffer[name_end+3]=='x' && buffer[name_end+4]=='i' && buffer[name_end+5]=='t');
        
        if(exit_){
            --active_clients;
            printf("\n");
            for(int i=0;i<name_end;i++) printf("%c",buffer[i]);
            printf(" left the chat.\n\n");
            printf("Active Clients: %d\n\n",active_clients);
            fflush(stdout);
            pthread_exit(NULL);
        }
        else{
            if(start){
                ++active_clients;
                printf("\n");
                for(int i=0;i<start;i++) printf("%c",buffer[i]);
                
                printf(" joined the chat.\n\n",buffer);
                printf("Active Clients: %d\n\n",active_clients);
            }
            else printf("%s",buffer);
            if (n < 0) error("ERROR writing to socket");
        }
        fflush(stdout);
    }
}

int main(int argc, char *argv[])
{   
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0)
            error("ERROR on binding");
    pthread_t thread_id;
    printf("Active Clients = %d\n",active_clients);
    while(1){
        listen(sockfd,5);
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        pthread_create(&thread_id,NULL,Clients,newsockfd);
        pthread_detach(thread_id);
        fflush(stdout);
    }
     return 0;
}