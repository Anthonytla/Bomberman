#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void server(char *argv, char *port) {
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
    int bindStatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind != 0)
        gai_strerror(bindStatus);
    int listenStatus = listen(sockfd, 10);
    if (listen != 0)
        gai_strerror(listenStatus);
    int addr_size = sizeof their_addr;
    int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    if (new_fd == -1)
        gai_strerror(new_fd);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 2;
    server(argv[1], argv[2]);
}