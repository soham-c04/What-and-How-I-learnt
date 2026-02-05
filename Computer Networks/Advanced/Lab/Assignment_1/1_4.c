#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <arpa/inet.h>

#define N 1024
#define HTML 16384

void error(char *msg){
    perror(msg);
    exit(1);
}

#define M 35

bool match(const char *text, const char *pattern) {
    if (pattern[0] == '\0') return true;

    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return false;

    int result = regexec(&re, text, 0, NULL, 0);
    regfree(&re);

    return result == 0;
}

const char *student_list[M] = {
    "Kasthuri Hrushikesh",
    "Aditya Dhananjay Singh",
    "Soham Chakraborty",
    "V V Venkata Satyanarayana Raju",
    "Varsha Swaraj",
    "Tanguturu Venkata Sai Pranav",
    "Gunupuru Sai Siddhartha",
    "Kondeti Aravind",
    "Kumar Snehal",
    "Varri Navya",
    "Atharva Atul Penkar",
    "Sanjay Kumar Pandit",
    "Banoth Ajay Vardhan Naik",
    "Meysakthivelan T",
    "Arkadipta Paul",
    "Avneel Singh",
    "Chetan",
    "Khem Singh",
    "Lingam Lokesh",
    "Oliver Kandir",
    "Peta Shanmuga Teja",
    "Rahul Dewangan",
    "Bikram Shahi",
    "Priyanka Kundu",
    "Abhishek Kumar",
    "Ashish Kumar",
    "Dev Patel",
    "Konisa Sai Sriyuktha",
    "Raj Kumar Singh",
    "Sandeep",
    "Seepana Mithun",
    "Shah Fenil Niteshbhai",
    "Singi Maharshi",
    "Sujeet Kumar Yadav",
    "Utsaw Kumar"
};

const char* print(char *regex) {
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
        "<h1>List of Students</h1>"
        "<hr>"
    );

    for (int i = 0; i < M; i++) {
        if(match(student_list[i],regex)){
            char line[256];
            sprintf(line, "<h3>%s</h3>", student_list[i]);
            strcat(html, line);
        }
    }

    strcat(html, "</body></html>");
    return html;
}

const char* count(char *regex) {
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
    );

    int count=0;
    for (int i = 0; i < M; i++) {
        if(match(student_list[i],regex)) count++;
    }
    char line[100];
    sprintf(line, "<h1>Count of Students: %d</h1></body></html>", count);
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
        char buffer[N];
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, sizeof(buffer));
        printf("Request received:\n%s\n", buffer);
        char method[100], path[100];
        sscanf(buffer, "%s %s", method, path);
        
        const char *html;
        char regex[100] = "";
        if((strlen(path)>=13) && (strncmp(path, "/print?regex=", 13)==0)){
            strncpy(regex, path+13, sizeof(regex)-1);
            html = print(regex);
        }
        else if(strncmp(path, "/count", 6) == 0){
            if((strlen(path)>=13) && (strncmp(path+6, "?regex=", 7)==0)){
                strncpy(regex, path+13, sizeof(regex)-1);
                html = count(regex);
            }
            else html=count(".*");
        }
        else html = print(".*");

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