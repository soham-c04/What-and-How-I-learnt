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

#define M 35

const char *student_list[M] = {
    "20CS02012 &emsp;&emsp;&emsp;&emsp; Kasthuri Hrushikesh",
    "22CS02001 &emsp;&emsp;&emsp;&emsp; Aditya Dhananjay Singh",
    "22CS02002 &emsp;&emsp;&emsp;&emsp; Soham Chakraborty",
    "22CS02003 &emsp;&emsp;&emsp;&emsp; Manthena V V Venkata Satyanarayana Raju",
    "22CS02005 &emsp;&emsp;&emsp;&emsp; Varsha Swaraj",
    "22CS02006 &emsp;&emsp;&emsp;&emsp; Tanguturu Venkata Sai Pranav",
    "22CS02007 &emsp;&emsp;&emsp;&emsp; Gunupuru Sai Siddhartha",
    "22CS02008 &emsp;&emsp;&emsp;&emsp; Kondeti Aravind",
    "22CS02009 &emsp;&emsp;&emsp;&emsp; Kumar Snehal",
    "22CS02010 &emsp;&emsp;&emsp;&emsp; Varri Navya",
    "22CS02011 &emsp;&emsp;&emsp;&emsp; Atharva Atul Penkar",
    "22CS02012 &emsp;&emsp;&emsp;&emsp; Sanjay Kumar Pandit",
    "22CS02013 &emsp;&emsp;&emsp;&emsp; Banoth Ajay Vardhan Naik",
    "22CS02014 &emsp;&emsp;&emsp;&emsp; Meysakthivelan T",
    "25CS06001 &emsp;&emsp;&emsp;&emsp; Arkadipta Paul",
    "25CS06002 &emsp;&emsp;&emsp;&emsp; Avneel Singh",
    "25CS06003 &emsp;&emsp;&emsp;&emsp; Chetan",
    "25CS06004 &emsp;&emsp;&emsp;&emsp; Khem Singh",
    "25CS06005 &emsp;&emsp;&emsp;&emsp; Lingam Lokesh",
    "25CS06006 &emsp;&emsp;&emsp;&emsp; Oliver Kandir",
    "25CS06007 &emsp;&emsp;&emsp;&emsp; Peta Shanmuga Teja",
    "25CS06008 &emsp;&emsp;&emsp;&emsp; Rahul Dewangan",
    "25CS06010 &emsp;&emsp;&emsp;&emsp; Bikram Shahi",
    "25CS06011 &emsp;&emsp;&emsp;&emsp; Priyanka Kundu",
    "25CS06012 &emsp;&emsp;&emsp;&emsp; Abhishek Kumar",
    "25CS06013 &emsp;&emsp;&emsp;&emsp; Ashish Kumar",
    "25CS06015 &emsp;&emsp;&emsp;&emsp; Dev Patel",
    "25CS06016 &emsp;&emsp;&emsp;&emsp; Konisa Sai Sriyuktha",
    "25CS06017 &emsp;&emsp;&emsp;&emsp; Raj Kumar Singh",
    "25CS06018 &emsp;&emsp;&emsp;&emsp; Sandeep",
    "25CS06019 &emsp;&emsp;&emsp;&emsp; Seepana Mithun",
    "25CS06020 &emsp;&emsp;&emsp;&emsp; Shah Fenil Niteshbhai",
    "25CS06021 &emsp;&emsp;&emsp;&emsp; Singi Maharshi",
    "25CS06022 &emsp;&emsp;&emsp;&emsp; Sujeet Kumar Yadav",
    "25CS06023 &emsp;&emsp;&emsp;&emsp; Utsaw Kumar"
};

int compare_by_name(const void *a, const void *b) {
    const char *s1 = *(const char **)a;
    const char *s2 = *(const char **)b;

    s1 = strchr(s1, ' ');
    s2 = strchr(s2, ' ');

    while (strncmp(s1, " &emsp;", 7) == 0) s1 += 7;
    while (strncmp(s2, " &emsp;", 7) == 0) s2 += 7;

    while (*s1 == ' ') s1++;
    while (*s2 == ' ') s2++;

    return strcmp(s1, s2);
}

const char* create_html(bool sort_by_name) {
    if (sort_by_name) {
        qsort(student_list, M, sizeof(char*), compare_by_name);
    }

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
        "<title>Assignment 1.3</title>" 
        "</head>"
        "<body>"
        "<h1>List of Students</h1>"
        "<hr>"
        "<hr>"
        "<h2>Roll No. &emsp;&emsp;&emsp; Name</h2>"
        "<hr>"
    );

    for (int i = 0; i < M; i++) {
        char line[256];
        sprintf(line, "<h3>%s</h3>", student_list[i]);
        strcat(html, line);
    }

    strcat(html, "</body></html>");

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
        
        const char *html = create_html((strcmp("sort",buffer)==0));
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