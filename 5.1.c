#define _LARGEFLE64_SOURCE 
#define _FILE_OFFSET_BITS 64
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

void printfAndExit(const char *s, ...)
{
    va_list list;
    va_start(list, s);
    vprintf(s, list);
    va_end(list);
    _exit(0);
}

int main(int argc, char *argv[])
{
    int fd;
    off_t off;
    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        printfAndExit("%s pathname offset\n", argv[0]);

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if(fd == -1)
        printfAndExit("打开失败\n");
    off = atoll(argv[2]);
    if(lseek(fd, off, SEEK_SET) == -1)
        printfAndExit("lseek失败\n");
    if(write(fd, "test", 4) == -1)
        printfAndExit("无法写入\n");
    close(fd);

    return 0;
}
