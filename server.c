#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void server(char *argv, char *port)
{
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    struct sockaddr_storage their_addr;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    socklen_t addr_size = sizeof their_addr;
    fd_set setFd;
    FD_ZERO(&setFd);
    int status = getaddrinfo(argv, port, &hints, &res);
    if (status != 0)
        printf("%s", gai_strerror(status));
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, 10);
    int client1 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    int client2 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    int client3 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    int client4 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    FD_SET(client1, &setFd);
    FD_SET(client2, &setFd);
    FD_SET(client3, &setFd);
    FD_SET(client4, &setFd);
    /*int bindStatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind != 0)
        gai_strerror(bindStatus);
    int listenStatus = listen(sockfd, 10);
    if (listenStatus != 0)
        gai_strerror(listenStatus);
    int addr_size = sizeof their_addr;

    char buff[10];
    int n;*/
    if (select(client4 + 1, &setFd, NULL, NULL, NULL) < 0)
            printf("error select\n");
    printf("Waiting for client...\n");
    while (1)
    {
        
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &setFd)) {
                
                if (new_fd == -1)
                    gai_strerror(new_fd);
                printf("New client\n");
                /*while ((n = read(new_fd, buff, 10)) > 0)
                {
                    printf("received %s", buff);
                    write(new_fd, "OK", 3);
                    memset(buff, '\0', 10);
                }*/
            close(i);
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 2;
    server(argv[1], argv[2]);
}