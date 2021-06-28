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

int read_client(int client) {

    int n = 0;
    char buff[128];

    if (client == -1)
        return 1;

    memset(buff, '\0', 128);
    while ((n = recv(client, buff, 128, 0)) >= 0) {
        if (n == 0)
            return -1;
        printf("Received %s:", buff);
        if (buff[n - 1] == '\n')
            break;
    }
    return 0;
    
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
    printf("Waiting for client...\n");
    int client1 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    printf("Client 1 connected\n");
    int client2 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    printf("Client 2 connected\n");
    /*int client3 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
    int client4 = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);*/
    fd_set setFd;
   // FD_SET(client2, &setFd);
    /*FD_SET(client3, &setFd);
    FD_SET(client4, &setFd);
    /*int bindStatus = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind != 0)
        gai_strerror(bindStatus);
    int listenStatus = listen(sockfd, 10);
    if (listenStatus != 0)
        gai_strerror(listenStatus);
    int addr_size = sizeof their_addr;*/
    while (1) {
        FD_ZERO(&setFd);

        FD_SET(client1, &setFd);
        FD_SET(client2, &setFd);

        select(client2 + 1, &setFd, NULL, NULL, NULL);
        if (FD_ISSET(client1, &setFd)) {
            if (read_client(client1) == -1) {
                printf("Client 1 disconnected");
                close(client1);
                client1 = -1;
            }
        }
        if (FD_ISSET(client2, &setFd)) {
            if (read_client(client2) == -1) {
                printf("Client 2 disconnected");
                close(client2);
                client2 = -1;
            }
        }

        if (client1 == -1 && client2 == -1)
            break;
        printf("looping\n");
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
        printf("sended from client %d :%s",sockfd, message);
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
    sleep(2);
    pthread_create(&client_id, NULL, &client, argv);
    pthread_create(&client_id2, NULL, &client, argv);
    while(1){};
}
