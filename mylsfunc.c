#include "myls.h"
#include <dirent.h>

extern int flag_a;

void judge_file(char * use_arg)//判断是文件还是目录
{
    struct stat arg; 
    if(stat(use_arg, &arg) != 0)
        perror("stat");

    switch (arg.st_mode & S_IFMT)
    {
        case S_IFDIR:
            dir_list(use_arg); 
            break;
        default:
            printf("this is not a dir\n");
            break;
    }
}

void dir_list(char * use_arg)
{
    DIR * dir; 
    struct dirent * entry;

    dir = opendir(use_arg);
    if(dir == NULL)
        perror("opendir");

    while ((entry = readdir(dir)) != NULL)
    {
        if(entry->d_name[0] == '.' && flag_a ==0)
            continue;
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
