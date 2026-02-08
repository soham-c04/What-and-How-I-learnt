#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
   char host[256];
   int hostname = gethostname(host, sizeof(host));
   struct hostent *host_entry = gethostbyname(host);
   char *IP = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
   
   printf("Current Host Name: %s\n", host);
   printf("Host IP: %s\n", IP);
}