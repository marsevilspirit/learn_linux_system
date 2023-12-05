#include "myls.h"
#include <dirent.h>
#include <stdio.h>

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


void list_i(struct dirent *list_name,  const char *dir_path)
{
    char path_i[PATH_MAX];
    sprintf(path_i, "%s/%s", dir_path, list_name->d_name);
    struct stat list_i;
    if(lstat(path_i, &list_i) == -1)
    {
        perror("stat_i");
        exit(EXIT_FAILURE);
    }

    printf("%6ld ", (long)list_i.st_ino);
}

void list_s(struct dirent *list_name,  const char *dir_path)
{
    char path_s[PATH_MAX];
    sprintf(path_s, "%s/%s", dir_path, list_name->d_name);
    struct stat list_s;
    if(lstat(path_s, &list_s) == -1)
    {
        perror("stat_s");
        exit(EXIT_FAILURE);
    }

    printf("%4ld ", (long)list_s.st_blocks/2);//为什么不一样
}

void list_l(struct dirent *list_name, const char *dir_path)//-l
{
    char path_l[PATH_MAX];
    sprintf(path_l, "%s/%s", dir_path, list_name->d_name);
    struct stat list_l;
    if(lstat(path_l, &list_l) == -1)
    {
        perror("stat_l");
        exit(EXIT_FAILURE);
    }

    switch(list_l.st_mode & S_IFMT)
    {
        case S_IFREG:  printf("-");         break;
        case S_IFDIR:  printf("d");         break;
        case S_IFCHR:  printf("c");         break;
        case S_IFBLK:  printf("b");         break;
        case S_IFLNK:  printf("i");         break;
        case S_IFIFO:  printf("p");         break;
        case S_IFSOCK: printf("s");         break;
    }
    printf("%c",(list_l.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c",(list_l.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c",(list_l.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c",(list_l.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c",(list_l.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c",(list_l.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c",(list_l.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c",(list_l.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c",(list_l.st_mode & S_IXOTH) ? 'x' : '-');
    printf(" %3ld",list_l.st_nlink);

    struct passwd * owner_info = getpwuid(list_l.st_uid);
    printf(" %s", owner_info->pw_name);
    struct group * group_info = getgrgid(list_l.st_gid);
    printf(" %s", group_info->gr_name);
    printf(" %6ld", list_l.st_size);

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
        perror("不是我的问题");
        return;
    }
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

void print_color(struct dirent * list_name, const char *dir_path)
{
    char path_color[PATH_MAX];
    sprintf(path_color, "%s/%s", dir_path, list_name->d_name);
    struct stat pr_color;
    memset(&pr_color, 0, sizeof(struct stat));
    if(stat(path_color, &pr_color) == -1)
    {
        perror("stat_color");
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

    if(flag_r == 1)
    {
        for(int j = n-1; j >= 0; j--)
        {
            if(flag_a == 0 && list_name[j]->d_name[0] == '.')
                continue;
            if (flag_i == 1)
                list_i(list_name[j], use_arg);   
            if(flag_s == 1)
                list_s(list_name[j], use_arg);
            if(flag_l == 1)
                list_l(list_name[j], use_arg);
            print_color(list_name[j], use_arg);
        }
    }
    else
    {
        for(int j = 0; j < n; j++)
        {
            if(flag_a == 0 && list_name[j]->d_name[0] == '.')
                continue;
            if (flag_i == 1)
                list_i(list_name[j], use_arg);   
            if(flag_s == 1)
                list_s(list_name[j], use_arg);
            if(flag_l == 1)
                list_l(list_name[j], use_arg);
            print_color(list_name[j], use_arg);
        } 
    }

    if (flag_R == 1)
    {
        rewinddir(dir);
        for (int j = 0; j < n; j++)
        {
            if (flag_a == 0 && list_name[j]->d_name[0] == '.')
                continue;
            if (list_name[j]->d_type == DT_DIR && strcmp(list_name[j]->d_name, ".") != 0 && strcmp(list_name[j]->d_name, "..") != 0)
            {
                printf("\n"BLUE"%s"RESET":\n", list_name[j]->d_name);
                char next_path[PATH_MAX];
                sprintf(next_path, "%s/%s", use_arg, list_name[j]->d_name);
                dir_list(next_path);
            }
        }
    }

    closedir(dir);
    free(list_name);
}





