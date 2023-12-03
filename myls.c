#include "myls.h"

extern int optind, opterr, optopt;
extern char * optarg;
int flag_a = 0, flag_l = 0;

int main(int argc, char *argv[]) {
    int opt, i = 1;
    int flag_use_arg = 0; // 标志是否有非命令行选项的命令行参数
    int j = 0;// 计算非选项参数的数量
    while (i < argc) {
        if (argv[i][0] != '-') {
            j++;
        }
        i++;
    }

    char **use_arg = (char **)malloc(j * sizeof(char *)); // 储存非命令行选项的命令行参数

    if (argc == 1) 
    {
        use_arg[0] = ".";
    }
    else {
        i = 1; // 重置 i 的值
        j = 0; // 重置 j 的值
               // 遍历命令行参数
        while (i < argc) 
        {
            if (argv[i][0] != '-') 
            {
                use_arg[j] = argv[i]; // 将非选项参数添加到目录数组中
                flag_use_arg = 1;
                j++;
            }
            i++;
        }

        if (flag_use_arg == 0) 
        {
            use_arg[0] = ".";
        }
    }
    while ((opt = getopt(argc, argv, "alRtris")) != -1)
    {
        switch (opt)
        {
            case 'a':      
                flag_a = 1;
                break;
            case 'l':
                flag_l = 1;
                break;
            case 'R':
                printf("we use R\n");
                break;
            case 't':
                printf("we use t\n");
                break;
            case 'r':
                printf("we use r\n");
                break;
            case 'i':
                printf("we use i\n");
                break;
            case 's':
                printf("we use s\n");
                break;
            case '?':
                printf("------------please don't do this-------------\n");
                break;
        }     
    }

    if(j == 0)
        judge_file(use_arg[0]);

    for (int k = 0; k < j; k++)
    {
        judge_file(use_arg[k]);
        printf("\n");
    } 
    // 释放动态分配的内存
    free(use_arg);

    return 0;
}
