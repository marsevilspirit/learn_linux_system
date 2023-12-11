#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    pipe(fd);

    switch (vfork())
    {
        case -1:
            perror("vfork");
            _exit(EXIT_FAILURE);
        case 0:
            close(fd[0]);
            printf("子进程关闭了文件描述符%d\n", fd[0]);
            _exit(EXIT_FAILURE);
        default:
            close(fd[1]);
            printf("父进程关闭了文件描述符%d\n",fd[1]);
            wait(NULL);
    } 
    return 0;
} 
