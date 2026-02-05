#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define N 1024
#define HTML 16384

void error(char *msg){
    perror(msg);
    exit(1);
}

const char* create_html() {
    return
        "<!DOCTYPE html>"
        "<html lang='en'>"
        "<head>"
        "<meta charset='UTF-8'>"
        "<title>Anime Page</title>"
        "<style>"
        "body {"
        "  margin: 0;"
        "  font-family: 'Segoe UI', Arial, sans-serif;"
        "  background: linear-gradient(135deg, #0f2027, #203a43, #2c5364);"
        "  color: #ffffff;"
        "}"
        ".container {"
        "  max-width: 1000px;"
        "  margin: auto;"
        "  padding: 40px;"
        "}"
        "h1 {"
        "  text-align: center;"
        "  font-size: 42px;"
        "  margin-bottom: 10px;"
        "}"
        "p {"
        "  text-align: center;"
        "  font-size: 18px;"
        "}"
        "a {"
        "  color: #ffcc70;"
        "  text-decoration: none;"
        "  font-weight: bold;"
        "}"
        "a:hover { text-decoration: underline; }"
        ".card {"
        "  background: rgba(255,255,255,0.08);"
        "  border-radius: 16px;"
        "  padding: 30px;"
        "  margin-top: 30px;"
        "  box-shadow: 0 15px 40px rgba(0,0,0,0.4);"
        "}"
        ".center { text-align: center; }"
        "img {"
        "  width: 260px;"
        "  border-radius: 14px;"
        "  margin-top: 20px;"
        "  box-shadow: 0 10px 25px rgba(0,0,0,0.5);"
        "}"
        ".lists {"
        "  display: flex;"
        "  gap: 40px;"
        "  margin-top: 30px;"
        "}"
        ".column { flex: 1; }"
        "h2 {"
        "  border-bottom: 2px solid #ffcc70;"
        "  padding-bottom: 5px;"
        "}"
        "ol { padding-left: 20px; }"
        "li { margin: 6px 0; }"
        "hr {"
        "  margin: 50px 0;"
        "  border: none;"
        "  height: 1px;"
        "  background: rgba(255,255,255,0.3);"
        "}"

        ".footer {"
        "max-width: 600px;"
        "margin: 40px auto;"
        "text-align: left;"
        "}"

        ".footer ul {"
        "list-style: none;"
        "padding-left: 144px;"
        "}"

        ".footer li {"
        "margin: 6px 0;"
        "}"
        
        "</style>"
        "</head>"

        "<body>"
        "<div class='container'>"

        "<h1>Created by: Soham Chakraborty</h1>"
        "<p style='font-size: 28px; font-weight: bold; color: orange;'>I like anime</p>"

        "<div class='center'>"
        "<img src='https://reactormag.com/wp-content/uploads/2024/09/frieren1.jpg' alt='Frieren'>"
        "</div>"

        "<p style='margin-top:20px;'>"
        "MyAnimeList: "
        "<a href='https://myanimelist.net/profile/Standard-Candle' target='_blank'>"
        "Standard-Candle</a>"
        "</p>"

        "<div class='card'>"
        "<h2 class='center'>Here's my</h2>"

        "<div class='lists'>"

        "<div class='column'>"
        "<h2>Top 10 Animes</h2>"
        "<ol>"
        "<li>Dragon Ball</li>"
        "<li>Naruto</li>"
        "<li>Death Note</li>"
        "<li>Frieren: Beyond Journey's End</li>"
        "<li>AOT Season 3</li>"
        "<li>Parasyte: The Maxim</li>"
        "<li>Dr. Stone</li>"
        "<li>Made in Abyss</li>"
        "<li>Spy x Family</li>"
        "<li>Daily Life of Highschool Boys</li>"
        "</ol>"
        "</div>"

        "<div class='column'>"
        "<h2>Top 10 Characters</h2>"
        "<ol>"
        "<li>Son Goku</li>"
        "<li>Uchiha Madara</li>"
        "<li>Jiraya</li>"
        "<li>Frieren</li>"
        "<li>Hori Chie</li>"
        "<li>Anya Forger</li>"
        "<li>Power</li>"
        "<li>Nel</li>"
        "<li>Kon</li>"
        "<li>Gon Freecss</li>"
        "</ol>"
        "</div>"

        "</div>"
        "</div>"

        "<hr>"

        "<div class='footer'>"
        "<b>Also Available On:</b>"
        "<a href='mailto:22cs02002@iitbbs.ac.in'>&nbsp;&nbsp;22cs02002@iitbbs.ac.in</a>"
        "<ul>"
        "<li><a href='https://github.com/soham-c04' target='_blank'>GitHub</a></li>"
        "<li><a href='https://www.linkedin.com/in/soham-chakraborty-02b55329a/' target='_blank'>LinkedIn</a></li>"
        "<li><a href='https://codeforces.com/profile/soham_c04' target='_blank'>Codeforces</a></li>"
        "<li><a href='https://www.codechef.com/users/soham_c04' target='_blank'>CodeChef</a></li>"
        "<li><a href='https://leetcode.com/u/soham_c04/' target='_blank'>LeetCode</a></li>"
        "</ul>"
        "</div>"

        "</div>"
        "</body>"
        "</html>";
}


int main(int argc, char *argv[]) {
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

    if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) error("ERROR on binding");;
    listen(sockfd, 5);
    printf("HTTP server running on port %d...\n", port);

    int client_fd = accept(sockfd, NULL, NULL);
    char buffer[N];
    read(client_fd, buffer, sizeof(buffer));
    printf("Request received:\n%s\n", buffer);

    const char *html = create_html();
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
    close(sockfd);

    return 0;
}