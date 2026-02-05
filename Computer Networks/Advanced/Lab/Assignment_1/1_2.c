#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define HOST "html.duckduckgo.com"
#define PORT "443"
#define N 1024

void format(char *dst, const char *src) {
    while (*src){
        if (*src == ' ') *dst++ = '+';
        else *dst++ = *src;
        src++;
    }
    *dst = '\0';
}

int main() {
    struct addrinfo serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.ai_family = AF_INET;
    serv_addr.ai_socktype = SOCK_STREAM;
    struct addrinfo *server;
    if(getaddrinfo(HOST, PORT, &serv_addr, &server)) {
        perror("getaddrinfo");
        return 1;
    }
    
    int sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    if(sockfd < 0) printf("ERROR opening socket\n");
    else if(connect(sockfd, server->ai_addr, server->ai_addrlen)<0) printf("Error Connecting\n");
    freeaddrinfo(server);

    SSL_library_init();
    SSL_load_error_strings();
    SSL_CTX *ctx;
    ctx = SSL_CTX_new(TLS_client_method());
    SSL *ssl;
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);
    SSL_connect(ssl);

    char query[N], encoded[N], buffer[N], request[N];
    printf("Enter search query: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0;
    format(encoded, query);

    snprintf(request, sizeof(request),
        "GET /html/?q=%s HTTP/1.1\r\n"
        "Host: " HOST "\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/120.0.0.0 Safari/537.36\r\n"
        "Connection: close\r\n\r\n",
        encoded);

    SSL_write(ssl, request, strlen(request));

    int bytes;
    while((bytes = SSL_read(ssl, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = 0;
        printf("%s", buffer);
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);

    return 0;
}
