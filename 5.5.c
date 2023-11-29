#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd1 = open("5.5.c", O_RDONLY);
    int fd2 = dup(fd1);
    while (1)
    {
        lseek(fd1, 1, SEEK_CUR);
        lseek(fd2, 1, SEEK_CUR);
        int flag1 = fcntl(fd1, F_GETFL);
        int flag2 = fcntl(fd2, F_GETFL);
        int lseek1 = lseek(fd1, 0, SEEK_CUR);
        int lseek2 = lseek(fd2, 0, SEEK_CUR);
        printf("%d %d %d %d\n", flag1, flag2, lseek1, lseek2);
        sleep(1);
    }
    return 0;
}
