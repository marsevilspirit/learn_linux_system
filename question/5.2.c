#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
struct atomic_append_struct{
    int fd;
    int x;
    const char * path;
    int num_bytes;
}atomic_append_info;

int main(int argc, const char *argv[])
{
    if(argc < 3)
    {
        printf("参数太少!\n");
        _exit(0);
    }
    atomic_append_info.path = argv[1];
    atomic_append_info.num_bytes = atoi(argv[2]);
    if(argc == 4 && strcmp(argv[3], "x") == 0)
    {
        atomic_append_info.x = 1;
    }
    else 
    {
        atomic_append_info.x = 0; 
    }
    printf("path %s, num-bytes %d, x %d\n",atomic_append_info.path, atomic_append_info.num_bytes, atomic_append_info.x);
    int openFlag;
    if(atomic_append_info.x)
    {
        openFlag = O_RDWR | O_CREAT;
    }
    else 
    {
        openFlag = O_RDWR | O_CREAT | O_APPEND;
    }
    atomic_append_info.fd = open(atomic_append_info.path, openFlag, 0777);
    if(atomic_append_info.fd == -1)
    {
        printf("打开文件失败\n");
        _exit(0);
    }

    char buff = 'a';
    for(int i = 0; i < atomic_append_info.num_bytes; i++)
    {
        if(atomic_append_info.x)
        {
            if(lseek(atomic_append_info.fd, 0, SEEK_END) == -1)
            {
                printf("无法lseek\n");
                _exit(0);
            }
        }
        if(write(atomic_append_info.fd, &buff, 1) == -1)
        {
            printf("无法写入\n");
            _exit(0);
        }
    }
    close(atomic_append_info.fd);
    return 0;
}
