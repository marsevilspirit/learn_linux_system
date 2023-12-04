#include "myls.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;

void list_name_sort(struct dirent ** list_name, int len)
{
    for(int i = 0; i < len; i++) 
    {

        for(int j = i + 1; j < len; j++)
        {
            struct stat stat_i;
            stat(list_name[i]->d_name, &stat_i);
            struct stat stat_j;
            stat(list_name[j]->d_name, &stat_j);

            if(stat_i.st_mtime < stat_j.st_mtime)
            {
                struct dirent * tmp = list_name[j];
                list_name[j] = list_name[i];
                list_name[i] = tmp;
            }
        }
    }
}

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
            file_list(use_arg);
            break;
    }
}

void file_list(char * use_arg)
{
    printf("%s", use_arg);
}

void dir_list(char * use_arg)
{
    DIR * dir; 
    struct dirent * entry;
    struct dirent ** list_name;//用于储存文件名,方便排序
    int n = 0, i = 0;//n记录文件数目,i为储存文件下标

    dir = opendir(use_arg);
    if(dir == NULL) 
        perror("opendir");

    while ((entry = readdir(dir)) != NULL)
        n++;
    rewinddir(dir);  

    list_name = (struct dirent **)malloc(n*sizeof(struct dirent *));
    if(list_name == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        list_name[i++] = entry; 
    }
    if(flag_t == 1)
        list_name_sort(list_name, i);

    for(int j = 0; j < n; j++)
    {
        if(flag_a == 0 && list_name[j]->d_name[0] == '.')
            continue;
        printf("%s\n", list_name[j]->d_name);
    }

    closedir(dir);
    free(list_name);
}




