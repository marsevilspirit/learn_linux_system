#include "myls.h"
#include <stdio.h>
extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;

void list_l(struct dirent *list_name, const char *dir_path)//-l
{
    char path_l[PATH_MAX];
    sprintf(path_l, "%s/%s", dir_path, list_name->d_name);
    struct stat list_l;
    if(stat(path_l, &list_l) == -1)
    {
        perror("stat_l");
        perror(path_l);
        return;
    }


    struct tm * tm_info = localtime(&list_l.st_mtime);
    char time_buffer[26];
    strftime(time_buffer, sizeof(time_buffer), "%_m月%_d日 %H:%M", tm_info);
    printf(" %s", time_buffer);   
    printf(" ");
}

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
    }
}

void print_color(struct dirent * list_name, const char *dir_path)
{
    char path_color[PATH_MAX];
    sprintf(path_color, "%s/%s", dir_path, list_name->d_name);
    struct stat pr_color;
    if(stat(path_color, &pr_color) == -1)
    {
        perror("print_color");
        perror(path_color);
        return;
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
        case S_IFDIR: printf(BLUE"%s"RESET"\n",list_name->d_name);    break; 
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
        // 拼接文件路径
        char file_path[PATH_MAX];
        sprintf(file_path, "%s/%s", use_arg, entry->d_name);

        // 检查文件访问权限
        if (access(file_path, R_OK) == -1)
        {
            printf("%s没有权限，无法打开\n", file_path);
            continue;// 跳过无权访问的文件
        }
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
        // 拼接文件路径
        char file_path[PATH_MAX];
        sprintf(file_path, "%s/%s", use_arg, entry->d_name);

        // 检查文件访问权限
        if (access(file_path, R_OK) == -1)
        {
            continue;// 跳过无权访问的文件
        }
        list_name[i] = (struct dirent *)malloc(sizeof(struct dirent));
        if (list_name[i] == NULL) 
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memcpy(list_name[i], entry, sizeof(struct dirent));
        i++;
    }

    for(int j = 0; j < n; j++)
    {
        if(flag_a == 0 && list_name[j]->d_name[0] == '.')
            continue;
        if(flag_l == 1)
            list_l(list_name[j], use_arg);
        print_color(list_name[j], use_arg);
    } 


    if (flag_R == 1)
    {
        for (int j = 0; j < n; j++)
        {
            if (flag_a == 0 && list_name[j]->d_name[0] == '.')
                continue;
            if (list_name[j]->d_type == DT_DIR && strcmp(list_name[j]->d_name, ".") != 0 && strcmp(list_name[j]->d_name, "..") != 0)
            {

                char next_path[PATH_MAX];
                char resolved_path[PATH_MAX];
                sprintf(next_path, "%s/%s", use_arg, list_name[j]->d_name);
                char* result = realpath(next_path, resolved_path);
                printf("\n"BLUE"%s"RESET":\n", resolved_path);
                if (result == NULL) 
                {
                    perror("realpath");
                }
                dir_list(next_path);
            }
        }
    }

    closedir(dir);

    for(int j = 0; j < i; j++)
    {
        free(list_name[j]);
    }
    free(list_name);
}




