#include "myshell.h"

void print_name()
{
    char hostname[256];
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    // 获取最后一个目录名
    char *last_dir = strrchr(cwd, '/');
    if (last_dir != NULL)
    {
        last_dir++; // 移动到下一个字符
    }
    gethostname(hostname, sizeof(hostname));
    printf(YELLOW"%s"RESET"@%s %s", getlogin(), hostname, last_dir);

}

void get_command()
{

}

