#include "myls.h"
#include <stdio.h>
#include <stdlib.h>

extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;


void judge_file(char * use_arg)//判断是文件还是目录
{
    struct stat arg; 
    if(stat(use_arg, &arg) != 0)
    {
        perror("stat1");
        return;
    }
    switch (arg.st_mode & S_IFMT)
    {
        case S_IFDIR:
            dir_list(use_arg); 
            break;
        default:
            return;
    }
}

void print_color(struct dirent * list_name, const char *dir_path)
{
    char path_color[PATH_MAX];
    sprintf(path_color, "%s/%s", dir_path, list_name->d_name);
    struct stat pr_color;
    if(stat(path_color, &pr_color) == -1)
    {
        perror(path_color);
        exit(EXIT_FAILURE);
    }
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
        case S_IFDIR: 
            printf(BLUE"%s"RESET"\n",list_name->d_name);    
            break; 
        default: 
            printf("%s\n",list_name->d_name);
            break;
            // exit(EXIT_FAILURE);
    }
}

void dir_list(char * use_arg)
{
    DIR * dir; 
    struct dirent * entry;
    struct dirent ** list_name;//用于储存文件名,方便排序
    struct stat file_stat;
    int n = 0, i = 0;//n记录文件数目,i为储存文件下标

    dir = opendir(use_arg);
    if(dir == NULL) 
    {
        perror("opendir");
        return;
    }
    // 拼接文件路径

    while ((entry = readdir(dir)) != NULL)
    {   
        n++;
    }

    rewinddir(dir);

    if (n == 0)
    {
        closedir(dir);
        return;
    }

    list_name = (struct dirent **)malloc(n*sizeof(struct dirent *));
    if(list_name == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        list_name[i] = (struct dirent *)malloc(sizeof(struct dirent));
        if (list_name[i] == NULL) 
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memcpy(list_name[i], entry, sizeof(struct dirent));
        //        printf("%d:%s\n", i, entry->d_name);
        i++;
    }

    for(int j = 0; j < n; j++)
    {
        if(flag_a == 0 && list_name[j]->d_name[0] == '.')
            continue;

        print_color(list_name[j], use_arg);
    } 

    closedir(dir);

    for(int j = 0; j < i; j++)
    {
        free(list_name[j]);
    }
    free(list_name);
}





