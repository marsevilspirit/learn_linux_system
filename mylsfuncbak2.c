#include "myls2.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;

void str_merge(char **arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char **left_arr = (char **)malloc(n1 * sizeof(char *));
    char **right_arr = (char **)malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_arr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (strcasecmp(left_arr[i], right_arr[j]) <= 0)
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }

    free(left_arr);
    free(right_arr);
}

void str_mergeSort(char **arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        str_mergeSort(arr, left, mid);
        str_mergeSort(arr, mid + 1, right);
        str_merge(arr, left, mid, right);
    }
}

void name_strcmp_sort(char **list_name, int len)
{
    str_mergeSort(list_name, 0, len - 1);
}

int compare_mtime(const char *file1, const char *file2, const char *dir_path) {
    struct stat st1, st2;
    char path1[255], path2[255];

    snprintf(path1, sizeof(path1), "%s/%s", dir_path, file1);
    snprintf(path2, sizeof(path2), "%s/%s", dir_path, file2);

    if (stat(path1, &st1) == -1 || stat(path2, &st2) == -1) {
        perror("stat");
        return 0;
    }

    if (st1.st_mtime < st2.st_mtime) {
        return 1;
    } else if (st1.st_mtime > st2.st_mtime) {
        return -1;
    } else {
        return 0;
    }
}

void merge(char **list_name, int left, int mid, int right, const char *dir_path) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char **left_list = malloc(n1 * sizeof(char *));
    char **right_list = malloc(n2 * sizeof(char *));

    for (i = 0; i < n1; i++) {
        left_list[i] = list_name[left + i];
    }
    for (j = 0; j < n2; j++) {
        right_list[j] = list_name[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (compare_mtime(left_list[i], right_list[j], dir_path) <= 0) {
            list_name[k] = left_list[i];
            i++;
        } else {
            list_name[k] = right_list[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        list_name[k] = left_list[i];
        i++;
        k++;
    }

    while (j < n2) {
        list_name[k] = right_list[j];
        j++;
        k++;
    }

    free(left_list);
    free(right_list);
}

void merge_sort(char **list_name, int left, int right, const char *dir_path) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(list_name, left, mid, dir_path);
        merge_sort(list_name, mid + 1, right, dir_path);

        merge(list_name, left, mid, right, dir_path);
    }
}

void list_name_sort(char **list_name, int i, const char *dir_path) {
    merge_sort(list_name, 0, i - 1, dir_path);
}

void list_i(char *list_name,  const char *dir_path)
{
    char path_i[PATH_MAX];
    sprintf(path_i, "%s/%s", dir_path, list_name);
    struct stat list_i;
    if(lstat(path_i, &list_i) == -1)
    {
        perror("stat_i");
        exit(EXIT_FAILURE);
    }

    printf("%6ld ", (long)list_i.st_ino);
}

void list_s(char *list_name,  const char *dir_path)
{
    char path_s[PATH_MAX];
    sprintf(path_s, "%s/%s", dir_path, list_name);
    struct stat list_s;
    if(lstat(path_s, &list_s) == -1)
    {
        perror("stat_s");
        exit(EXIT_FAILURE);
    }

    printf("%6ld ", (long)list_s.st_blocks/2);//为什么不一样
}

void list_l(char *list_name, const char *dir_path)//-l
{
    char path_l[PATH_MAX];
    sprintf(path_l, "%s/%s", dir_path, list_name);
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
    //struct group * group_info = getgrgid(list_l.st_gid);//这是一个废物和函数，不要去用它
    //printf(" %s", group_info->gr_name);
    printf(" %s", owner_info->pw_name);
    printf(" %8ld", list_l.st_size);

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
        default:
            return;
    }
}

void print_color(char * list_name, const char *dir_path)
{
    char path_color[PATH_MAX];
    sprintf(path_color, "%s/%s", dir_path, list_name);
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
                printf(GREEN "%s" RESET "\n", list_name);  // 可执行文件
            } 
            else  
            {
                printf(YELLOW"%s"RESET"\n", list_name);  // 普通文件
            }              
            break;
        case S_IFDIR: 
            printf(BLUE"%s"RESET"\n",list_name);    
            break; 
        default: 
            printf("%s\n",list_name);
            break;
            // exit(EXIT_FAILURE);
    }
}

void dir_list(char * use_arg)
{
    DIR * dir; 
    struct dirent * entry;
    char ** list_name;//用于储存文件名,方便排序
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
            // 跳过无权访问的文件
            continue;
        }
        n++;
    }

    rewinddir(dir);

    if (n == 0)
    {
        closedir(dir);
        return;
    }

    list_name = (char **)malloc(n*sizeof(char *));
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
            printf("%s没有权限，无法打开\n", file_path);
            continue;// 跳过无权访问的文件
        }
        list_name[i] = (char *)malloc(sizeof(char)*256);
        if (list_name[i] == NULL) 
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(list_name[i], entry->d_name);
        //        printf("%d:%s\n", i, entry->d_name);
        i++;
    }

    if(flag_t == 0)
        name_strcmp_sort(list_name, i);
    else
        list_name_sort(list_name, i, use_arg);

    if(flag_r == 1)
    {
        for(int j = n-1; j >= 0; j--)
        {
            if(flag_a == 0 && list_name[j][0] == '.')
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
            if(flag_a == 0 && list_name[j][0] == '.')
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

    rewinddir(dir);

    if (flag_R == 1)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (flag_a == 0 && entry->d_name[0] == '.')
                continue;    
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {

                char next_path[PATH_MAX];
                char resolved_path[PATH_MAX];
                sprintf(next_path, "%s/%s", use_arg, entry->d_name);
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







