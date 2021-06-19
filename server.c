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
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *test(void *argv) {

    printf("%s" , (char *)argv);
    pthread_exit(NULL);
}

void *server(void *argv)
{
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    struct sockaddr_storage their_addr;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    socklen_t addr_size = sizeof their_addr;
    
    //(char *)argv[strlen((char *)argv) - 1] = '\0';
    //argv[1][strlen(argv[1]) - 1] = '\0';

    int status = getaddrinfo(NULL, argv, &hints, &res);
    if (status != 0)
        printf("%s", gai_strerror(status));
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    int yes = 1;
    bind(sockfd, res->ai_addr, res->ai_addrlen);
    listen(sockfd, 10);
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
        perror("setsockopt");
        exit(1);
    } 
    int client1 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    int client2 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    /*int client3 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    int client4 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);*/
    fd_set setFd;
    FD_ZERO(&setFd);
    FD_SET(client1, &setFd);
    FD_SET(client2, &setFd);
    /*FD_SET(client3, &setFd);
    FD_SET(client4, &setFd);
    /*int bindStatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind != 0)
        gai_strerror(bindStatus);
    int listenStatus = listen(sockfd, 10);
    if (listenStatus != 0)
        gai_strerror(listenStatus);
    int addr_size = sizeof their_addr;*/
    char buff[10];
    int n;
    
    printf("Waiting for client...\n");
    int select1;
    while (1)
    {
        if ((select1 = select(client2 + 1, &setFd, NULL, NULL, NULL)) < 0)
            printf("error %s\n", gai_strerror(select1));
        for (int i = 0; i < client2 + 1; i++) {
            if (FD_ISSET(i, &setFd)) {
                while ((n = read(i, buff, 10)) > 0)
                {
                    printf("received from %d - %s",i, buff);
                    write(i, "OK", 3);
                    memset(buff, '\0', 10);
                }
                /*else
                {
                    printf("client %d disconnected", i);
                    break;
                }*/
            close(i);
            }
        }
    }
    return NULL;
}

void *client(void *argv) {
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    struct sockaddr_storage their_addr;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    //argv = (char *)argv;
    //argv[strlen(argv) - 1] = '\0';
    //argv[1][strlen(argv[1]) - 1] = '\0';
    int status = getaddrinfo(NULL, argv, &hints, &res);
    if (status != 0)
        printf("1%s", gai_strerror(status));
    
    int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    int new_fd = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (new_fd < 0)
        printf("2%s", gai_strerror(new_fd));
    char message[128];
    while (1)
    {
        memset(message, '\0', 128);
        fgets(message, 128, stdin);
        if (write(sockfd, message, strlen(message)) < 0) {
            printf("send failed");
            close(sockfd);
            return NULL;
        }
        printf("sended %s", message);
        read(sockfd, message, 3);
        printf("%s\n", message);
        memset(message, '\0', 128);
    }
    close(sockfd);
    return NULL;
}

int main(void)
{
    //char *ip = NULL;
    char *port = NULL;
    size_t len = 0;

    //printf("Enter server IP\n");
    //getline(&ip, &len, stdin);
    printf("Enter server port\n");
    getline(&port, &len, stdin);
    port[strlen(port) - 1] = '\0';

    //char *argv[2] = {ip, port};
    char *argv = port;
    pthread_t server_id;
    pthread_t client_id;
    pthread_t client_id2;

    pthread_create(&server_id, NULL, &server, argv);
    
    //pthread_join(server_id, NULL);
    pthread_create(&client_id, NULL, &client, argv);
    pthread_create(&client_id2, NULL, &client, argv);
    while(1);
}