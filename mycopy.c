#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("整不明白咋使吗？./mycopy 复制文件 粘贴文件");
        exit(EXIT_FAILURE);
    }

    int source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("打开要复制的文件失败了，你的问题");
        exit(EXIT_FAILURE);
    }

    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("打开也不行，创建也不行，你的问题");
        close(source_fd);
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t read_bytes, write_bytes;

    while ((read_bytes = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        write_bytes = write(dest_fd, buffer, read_bytes);
        if (write_bytes == -1) {
            perror("写不进去，你的问题");
            close(source_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (read_bytes == -1) {
        perror("读不了，你的问题");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    close(source_fd);
    close(dest_fd);

    return 0;
}
