#include "myls.h"
#include <stdlib.h>

extern int flag_a, flag_l, flag_R, flag_t, flag_r, flag_i, flag_s;

void str_merge(struct dirent **list_name, int low, int mid, int high) {
    int left_size = mid - low + 1;
    int right_size = high - mid;

    struct dirent **left_list = (struct dirent **)malloc(left_size * sizeof(struct dirent *));
    struct dirent **right_list = (struct dirent **)malloc(right_size * sizeof(struct dirent *));

    // 将原始列表分成左右两个子列表
    for (int i = 0; i < left_size; i++) {
        left_list[i] = list_name[low + i];
    }
    for (int j = 0; j < right_size; j++) {
        right_list[j] = list_name[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;

    // 合并左右子列表，按照字符串比较排序
    while (i < left_size && j < right_size) {
        if (strcasecmp(left_list[i]->d_name, right_list[j]->d_name) <= 0) {
            list_name[k] = left_list[i];
            i++;
        } else {
            list_name[k] = right_list[j];
            j++;
        }
        k++;
    }

    // 将剩余的元素复制到列表中
    while (i < left_size) {
        list_name[k] = left_list[i];
        i++;
        k++;
    }
    while (j < right_size) {
        list_name[k] = right_list[j];
        j++;
        k++;
    }

    free(left_list);
    free(right_list);
}

void str_merge_sort(struct dirent **list_name, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        // 递归地对左右子列表进行归并排序
        str_merge_sort(list_name, low, mid);
        str_merge_sort(list_name, mid + 1, high);

        // 合并左右子列表
        str_merge(list_name, low, mid, high);
    }
}

void name_strcmp_sort(struct dirent **list_name, int len) {
    str_merge_sort(list_name, 0, len - 1);
}

void time_merge(struct dirent **list_name, int low, int mid, int high, const char *dir_path) 
{
    int left_size = mid - low + 1;
    int right_size = high - mid;

    struct dirent **left_list = (struct dirent **)malloc(left_size * sizeof(struct dirent *));
    struct dirent **right_list = (struct dirent **)malloc(right_size * sizeof(struct dirent *));

    // 将原始列表分成左右两个子列表
    for (int i = 0; i < left_size; i++) 
    {
        left_list[i] = list_name[low + i];
    }
    for (int j = 0; j < right_size; j++) 
    {
        right_list[j] = list_name[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
    struct stat stat_left, stat_right;

    // 合并左右子列表，按照修改时间排序
    while (i < left_size && j < right_size) 
    {
        char path_left[PATH_MAX], path_right[PATH_MAX];
        sprintf(path_left, "%s/%s", dir_path, left_list[i]->d_name);
        sprintf(path_right, "%s/%s", dir_path, right_list[j]->d_name);

        if (lstat(path_left, &stat_left) == -1 || lstat(path_right, &stat_right) == -1) 
        {
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        if (stat_left.st_mtime <= stat_right.st_mtime) 
        {
            list_name[k] = left_list[i];
            i++;
        } else {
            list_name[k] = right_list[j];
            j++;
        }
        k++;
    }

    // 将剩余的元素复制到列表中
    while (i < left_size) 
    {
        list_name[k] = left_list[i];
        i++;
        k++;
    }
    while (j < right_size) 
    {
        list_name[k] = right_list[j];
        j++;
        k++;
    }

    free(left_list);
    free(right_list);
}

void time_merge_sort(struct dirent **list_name, int low, int high, const char *dir_path) 
{
    if (low < high) {
        int mid = low + (high - low) / 2;

        // 递归地对左右子列表进行归并排序
        time_merge_sort(list_name, low, mid, dir_path);
        time_merge_sort(list_name, mid + 1, high, dir_path);

        // 合并左右子列表
        time_merge(list_name, low, mid, high, dir_path);
    }
}

void list_name_sort(struct dirent **list_name, int len, const char *dir_path) 
{
    time_merge_sort(list_name, 0, len - 1, dir_path);
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

    printf("%6ld ", (long)list_s.st_blocks/2);//为什么不一样
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
            printf("%s没有权限，无法打开\n", file_path);
            continue;// 跳过无权访问的文件
        }
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

    if(flag_t == 0)
        name_strcmp_sort(list_name, i);
    else
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







