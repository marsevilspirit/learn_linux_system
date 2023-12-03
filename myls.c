#include "myls.h"

int main(int argc, char *argv[]) {
    int i = 1;
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
    
for (int k = 0; k <= j; k++)
{
    judge_file(use_arg[k]);
} 
    // 释放动态分配的内存
    free(use_arg);

    return 0;
}
