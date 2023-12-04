#include "myls.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;

int compare_mtime(const void *a, const void *b) {
    const struct dirent *entry1 = *(const struct dirent **)a;
    const struct dirent *entry2 = *(const struct dirent **)b;

    struct stat stat1, stat2;
    stat(entry1->d_name, &stat1);
    stat(entry2->d_name, &stat2);

    if (stat1.st_mtime < stat2.st_mtime)
        return 1;
    else if (stat1.st_mtime > stat2.st_mtime)
        return -1;
    else
        return 0;
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

    closedir(dir);

    if(flag_t == 1)
        qsort(list_name, n, sizeof(struct dirent *), compare_mtime);

    for(int i = 0; i < n; i++)
    {
        if(flag_a == 0 && list_name[i]->d_name[0] == '.')
            continue;
        printf("%s\n", list_name[i]->d_name);
    }

    free(list_name);
}




