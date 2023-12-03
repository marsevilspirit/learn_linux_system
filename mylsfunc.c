#include "myls.h"
#include <stdio.h>
#include <sys/stat.h>

void judge_file(char * use_arg)//判断是文件还是目录
{
    struct stat arg; 
    if(stat(use_arg, &arg) != 0)
        perror("stat");
    
    switch (arg.st_mode & S_IFMT)
    {
        case S_IFDIR:
            printf("this is a dir\n");
            break;
        default:
            printf("this is not a dir\n");
            break;
    }
}
