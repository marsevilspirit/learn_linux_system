#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT_NUM 8000
#define IP "10.30.0.245"
#define BUF_SIZE 2048

void errExit(const char* error)
{
    perror(error);
    exit(EXIT_FAILURE);
}

int writen(int fd, const char* msg, int size)
{
    const char* buf = msg;
    int count = size;
    while(count > 0)
    {
        int len = send(fd, buf, count, 0);
        if(len == -1)
        {
            close(fd);
            return -1;
        }
        else if(len == 0)
        {
            continue;
        }

        buf += len;
        count -= len;
    }

    return size;
}

int sendMsg(int cfd, const char* msg, int len)
{
    if(msg == NULL || len <= 0 || cfd <= 0)
    {
        return -1;
    }

    char* data = (char*)malloc(len+4);
    int bigLen = htonl(len);
    memcpy(data, &bigLen, 4);
    memcpy(data+4, msg, len);

    int ret = writen(cfd, data, len+4);

    free(data);

    return ret;
}

int main(void) {
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

    while(true){
        printf("\nPlease input: ");
        memset(buf, 0, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        int len = strlen(buf);
        
        // 去除输入内容末尾的换行符
        if (len > 0 && buf[len-1] == '\n') {
            buf[len-1] = '\0';
            len--;
        }

        if(buf[0] == '\0')
            continue;

        if (strcmp(buf, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }

        if(sendMsg(sfd, buf, len) == -1)
            errExit("sendMsg");
    }

    if(close(sfd) == 0)
        printf("close success");

    return 0;
}
