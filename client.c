#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void client(char *argv, char *port) {
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    struct sockaddr_storage their_addr;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(argv, port, &hints, &res);
    if (status != 0)
        printf("%s", gai_strerror(status));
    
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    int new_fd = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (new_fd < 0)
        printf("%s", gai_strerror(new_fd));
    char message[128];
    while (1)
    {
        memset(message, '\0', 128);
        fgets(message, 128, stdin);
        if (write(sockfd, message, strlen(message)) < 0) {
            printf("send failed");
            close(sockfd);
            return;
        }
        printf("sended %s", message);
        read(sockfd, message, 3);
        printf("%s\n", message);
        memset(message, '\0', 128);
    }
    close(sockfd);
    return;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 2;
    client(argv[1], argv[2]);
}