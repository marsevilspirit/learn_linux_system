#include "myls.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;

void name_strcmp_sort(struct dirent **list_name, int len) 
{
    for (int i = 0; i < len - 1; i++) 
    {
        for (int j = i + 1; j < len; j++) 
        {
            if (strcasecmp((list_name[i]->d_name), list_name[j]->d_name) > 0) 
            {
                struct dirent *tmp = list_name[j];
                list_name[j] = list_name[i];
                list_name[i] = tmp;
            }
        }
    }
}

void list_name_sort(struct dirent ** list_name, int len, const char *dir_path)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++) 
        {
            char path_i[PATH_MAX];
            sprintf(path_i, "%s/%s", dir_path, list_name[i]->d_name);
            struct stat stat_i;
            lstat(path_i, &stat_i);
            time_t mtime_i = stat_i.st_mtime;

            char path_j[PATH_MAX];
            sprintf(path_j, "%s/%s", dir_path, list_name[j]->d_name);
            struct stat stat_j;
            lstat(path_j, &stat_j);
            time_t mtime_j = stat_j.st_mtime;

            if (mtime_i < mtime_j)
            {
                struct dirent *tmp = list_name[j];
                list_name[j] = list_name[i];
                list_name[i] = tmp;
            }
        }
    }
}

void list_l(struct dirent *list_name)//-l
{

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

void print_color(struct dirent * list_name)
{
    struct stat pr_color;
    stat(list_name->d_name, &pr_color);

    switch (pr_color.st_mode & S_IFMT)
    {
        case S_IFREG: 
            if (pr_color.st_mode & S_IXUSR) 
            {
                printf(GREEN "%s" RESET "\n", list_name->d_name);  // 可执行文件
            } 
            else 
            {
                printf(YELLOW"%s"RESET"\n", list_name->d_name);  // 普通文件
            }              
            break;
        case S_IFDIR: printf(BLUE"%s"RESET"\n",list_name->d_name);    break; 
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

    name_strcmp_sort(list_name, i);
    if(flag_t == 1)
        list_name_sort(list_name, i, use_arg);

    for(int j = 0; j < n; j++)
    {
        if(flag_a == 0 && list_name[j]->d_name[0] == '.')
            continue;
        if(flag_l == 1)
            list_l(list_name[j]);
        print_color(list_name[j]);
    }

    closedir(dir);
    free(list_name);
}





