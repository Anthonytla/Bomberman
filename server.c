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

    char *ports[4] = {"8000", "8001", "8002", "8003"};
    fd_set setFd;
    FD_ZERO(&setFd);
    for (int i = 0; i < 4; i++)
    {

        int status = getaddrinfo(argv, ports[i], &hints, &res);
        if (status != 0)
            printf("%s", gai_strerror(status));
        int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    }

    int bindStatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind != 0)
        gai_strerror(bindStatus);
    int listenStatus = listen(sockfd, 10);
    if (listenStatus != 0)
        gai_strerror(listenStatus);
    int addr_size = sizeof their_addr;

    char buff[10];
    int n;
    printf("Waiting for client...\n");
    while (1)
    {
        int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
        if (new_fd == -1)
            gai_strerror(new_fd);
        printf("New client\n");
        while ((n = read(new_fd, buff, 10)) > 0)
        {
            printf("received %s", buff);
            write(new_fd, "OK", 3);
            memset(buff, '\0', 10);
        }
    }
    close(sockfd);
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 2;
    server(argv[1], argv[2]);
}