#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_NUM 50000
#define IP "10.30.0.245"
#define BUF_SIZE 2048

void errExit(const char* error)
{
    perror(error);
    exit(EXIT_FAILURE);
}

int main(void)
{
    int sfd;
    struct sockaddr_in svaddr;
    char buf[BUF_SIZE];

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1)
        errExit("socket");

    memset(&svaddr, 0, sizeof(struct sockaddr_in)); 
    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(PORT_NUM);
    inet_pton(AF_INET, IP, &svaddr.sin_addr);

    if(connect(sfd, (const struct sockaddr*) &svaddr, sizeof(struct sockaddr_in)) == -1)
        errExit("connect");

    printf("\nPlease input: ");
    scanf("%s", buf);
    send(sfd, buf, strlen(buf), 0);
    memset(buf, 0, BUF_SIZE);
    recv(sfd, buf, BUF_SIZE-1, 0);
    printf("Recv: %s\n", buf);
    close(sfd);
    return 0;
}



