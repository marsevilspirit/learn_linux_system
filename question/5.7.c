#include <stdio.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>

int myreadv(int fd, struct iovec *iov, int len)
{
    int totalLen = 0;
    for(int i = 0; i < len; i++)
    {
        totalLen += iov[i].iov_len;
    }
    for(int i = 0; i < len; i++)
    {
        for(int j = 0; j < iov[i].iov_len; j++)
        {
            if(read(fd, iov[i].iov_base+j, 1) == -1)
            {
                printf("读取失败\n");
                _exit(0);
            }
        }
    }
    return totalLen;
}

int mywritev(int fd, struct iovec *iov, int len)
{
    int totalLen = 0;
    for(int i = 0; i < len; i++)
    {
        totalLen += iov[i].iov_len;
    }
    void *buff = malloc(totalLen);
    int start = 0;
    for(int i = 0; i < len; i++)
    {
        memcpy(buff+start, iov[i].iov_base, iov[i].iov_len);
        start += iov[i].iov_len;
    }
    if(write(fd, buff, totalLen) == -1)
    {
        printf("写入失败\n");
        _exit(0);
    }
    free(buff);
    return totalLen;
}

int main(void)
{
    char buf1[5], buf2[10];
    struct iovec iov[2];
    iov[0].iov_base = buf1;
    iov[0].iov_len = 5;
    iov[1].iov_base = buf2;
    iov[1].iov_len = 10;

    int fd = open("a.txt", O_RDWR);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }

    int rsize = myreadv(fd, iov, 2);
    printf("rsize = %d\n",rsize);

    close(fd);

    fd = open("b.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd < 0)
    {
        perror("open");
        return -1;
    }

    int wsize = mywritev(fd, iov, 2);
    printf("wsize = %d\n", wsize);

    close(fd);
    return 0;
}
