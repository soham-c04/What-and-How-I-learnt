#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define N 1024
#define HTML 16384

void error(char *msg){
    perror(msg);
    exit(1);
}

const char* homepage() {
    char *html = malloc(HTML);
    html[0] = '\0';

    strcat(html,
        "<!DOCTYPE html>"
        "<html lang=\"en\">" 
        "<head>" 
        "<meta charset=\"UTF-8\">" 
        "<meta name=\"Name\" content=\"Soham Chakraborty\">" 
        "<meta name=\"Roll No.\" content=\"22CS02002\">" 
        "<meta name=\"Branch\" content=\"CSE Dual Degree\">" 
        "<meta name=\"Semester\" content=\"8\">" 
        "<link rel=\"icon\" href=\"logo_iit_bbs.png\" type=\"image/x-icon\">" 
        "<title>Assignment 1.5</title>" 
        "</head>"
        "<body>"
        "<h1>Calculator</h1>"
        "<hr>"
        "<h3>Available services:</h3>"
        "<h3>/calc?op=add|sub|mul|div&a=X&b=Y</h3>"
        "</body>"
        "</html>"
    );
    return html;
}

const char* calculator(char *op, char *a, char *b) {
    char *html = malloc(HTML);
    html[0] = '\0';

    strcat(html,
        "<!DOCTYPE html>"
        "<html lang=\"en\">" 
        "<head>" 
        "<meta charset=\"UTF-8\">" 
        "<meta name=\"Name\" content=\"Soham Chakraborty\">" 
        "<meta name=\"Roll No.\" content=\"22CS02002\">" 
        "<meta name=\"Branch\" content=\"CSE Dual Degree\">" 
        "<meta name=\"Semester\" content=\"8\">" 
        "<link rel=\"icon\" href=\"logo_iit_bbs.png\" type=\"image/x-icon\">" 
        "<title>Assignment 1.4</title>" 
        "</head>"
        "<body>"
        "<h1> Result: "
    );

    int X = atoi(a), Y = atoi(b);
    int result;
    char line[100];
    if(strcmp(op, "add") == 0) result = X+Y;
    else if(strcmp(op, "sub") == 0) result = X-Y;
    else if(strcmp(op, "mul") == 0) result = X*Y;
    else if(strcmp(op, "div") == 0) result = X/Y;
    else{
        strcat(html, "Unrecognized Operation</h1></body></html>");
        return html;
    }
    sprintf(line, "%d</h1></body></html>", result);
    strcat(html, line);
    return html;
}


int main(int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    int port = atoi(argv[1]), sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0) error("Error opening socket");
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) error("ERROR on binding");
        printf("HTTP server running on port %d...\n", port);

    while(true){
        listen(sockfd, 5);

        int client_fd = accept(sockfd, NULL, NULL);
        char buffer[N], method[100], path[100];
        memset(buffer, 0, sizeof(buffer));
        memset(method, 0, sizeof(method));
        memset(path, 0, sizeof(path));
        read(client_fd, buffer, sizeof(buffer));
        printf("Request received:\n%s\n", buffer);
        sscanf(buffer, "%s %s", method, path);
        int n = strlen(path);

        const char *html;
        char op[4] = "", a[10]="", b[10]="";
        if((n>=20) && (strncmp(path, "/calc?op=", 9)==0)){
            strncpy(op, path+9, 3); op[3] = '\0';
            int i,j;
            for(j=0, i=15;(i<n) && (path[i]!='&');i++){
                if((j<9) && (path[i]>='0') && (path[i]<='9')){
                    a[j++]=path[i];
                }
            }
            for(j=0, i+=3;i<n;i++){
                if((j<9) && (path[i]>='0') && (path[i]<='9')){
                    b[j++]=path[i];
                }
            }
        }
        
        printf("a: %s\nb: %s\n", a, b);
        if((strlen(a)>0) && (strlen(b)>0)) html = calculator(op, a, b);
        else html = homepage();

        char response[HTML];
        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %lu\r\n"
            "Connection: close\r\n\r\n"
            "%s",
            strlen(html), html);    

        write(client_fd, response, strlen(response));
        close(client_fd);
    }

    close(sockfd);

    return 0;
}