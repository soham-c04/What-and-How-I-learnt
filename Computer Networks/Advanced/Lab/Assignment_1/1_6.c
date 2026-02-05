#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <arpa/inet.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#define min(a,b) (((a)<(b))? (a):(b))
#define N 1024
#define HTML 16384
#define WS_GUID "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

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

    for (int i = 0; i < M; i++) {
        if(match(student_list[i],regex)){
            char line[256];
            sprintf(line, "%s\n", student_list[i]);
            strcat(html, line);
        }
    }

    return html;
}

const char* count(char *regex) {
    char *html = malloc(HTML);
    html[0] = '\0';

    int count=0;
    for (int i = 0; i < M; i++) {
        if(match(student_list[i],regex)) count++;
    }
    
    char line[10];
    sprintf(line, "%d\n", count);
    strcat(html, line);
    return html;
}

const char* invalid_command(){
    return  "Invalid Command\n";
}

void websocket_handshake(int client_fd, char *request) {
    char *key_start = strstr(request, "Sec-WebSocket-Key:");
    if (!key_start) return;
    key_start += strlen("Sec-WebSocket-Key: ");

    char client_key[128];
    sscanf(key_start, "%s", client_key);

    char combined[256];
    snprintf(combined, sizeof(combined), "%s%s", client_key, WS_GUID);

    unsigned char sha1_hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)combined, strlen(combined), sha1_hash);

    char accept_key[256];
    EVP_EncodeBlock((unsigned char *)accept_key, sha1_hash, SHA_DIGEST_LENGTH);

    char response[512];
    snprintf(response, sizeof(response),
        "HTTP/1.1 101 Switching Protocols\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Accept: %s\r\n\r\n",
        accept_key
    );

    
    write(client_fd, response, strlen(response));
}

void convert(unsigned char *message) {
    int payload_len = message[1] & 0x7F;
    unsigned char *mask = message + 2;
    unsigned char *payload = message + 6;

    unsigned char temp[N];
    for (int i = 0; i < payload_len; i++)
        temp[i] = payload[i] ^ mask[i % 4];
    temp[payload_len] = '\0';

    memcpy(message, temp, payload_len + 1);
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
    printf("WebSocket server running on port %d...\n", port);

    listen(sockfd, 5);
    int client_fd = accept(sockfd, NULL, NULL);

    char buffer[N]={0};
    read(client_fd, buffer, sizeof(buffer));
    websocket_handshake(client_fd, buffer);

    while(true){
        unsigned char message[N];
        memset(message, 0, sizeof(message));
        int sz = read(client_fd, message, sizeof(message));
        if(sz <= 0) break;

        convert(message);
        printf("Request Received: %s\n", message);
        int len = strlen(message);
        for(int i=0;i<min(len,5);i++) message[i] |= 32;

        const char *html;
        if((len>=5) && (strncmp(message, "print", 5)==0)){
            if(len>=7){
                char regex[100] = "";
                strncpy(regex, message+6, sizeof(regex)-1);
                html = print(regex);
            }
            else html = print(".*");
        }
        else if((len>=5) && (strncmp(message, "count", 5)==0)){
            if(len>=7){
                char regex[100] = "";
                strncpy(regex, message+6, sizeof(regex)-1);
                html = count(regex);
            }
            else html = count(".*");
        }
        else html = invalid_command();
        int n = strlen(html);
        
        unsigned char header[10];
        int header_len;

        header[0] = 0x81;  

        if (n <= 125) {
            header[1] = n;
            header_len = 2;
        }
        else if (n <= 65535) {
            header[1] = 126;
            header[2] = (n >> 8) & 0xFF;
            header[3] = n & 0xFF;
            header_len = 4;
        }
        else {
            header[1] = 127;
            for (int i = 0; i < 8; i++)
                header[2 + i] = (n >> (56 - 8*i)) & 0xFF;
            header_len = 10;
        }   

        write(client_fd, header, header_len);
        write(client_fd, html, n);    
    }

    close(client_fd);
    close(sockfd);

    return 0;
}