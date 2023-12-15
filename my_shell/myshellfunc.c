#include "myshell.h"
#include <stdio.h>

void print_myshell()
{
    printf("%s\n", LINES);
    printf(" __    __     __  __        ______     __  __     ______   ______     ______        ______     __  __     ______     __         __        \n");
    printf("/\\ \"-./  \\   /\\ \\_\\ \\      /\\  ___\\   /\\ \\/\\ \\   /\\  == \\ /\\  ___\\   /\\  == \\      /\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\       /\\ \\       \n");
    printf("\\ \\ \\-./\\ \\  \\ \\____ \\     \\ \\___  \\  \\ \\ \\_\\ \\  \\ \\  _-/ \\ \\  __\\   \\ \\  __<      \\ \\___  \\  \\ \\  __ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \n");
    printf(" \\ \\_\\ \\ \\_\\  \\/\\_____\\     \\/\\_____\\  \\ \\_____\\  \\ \\_\\    \\ \\_____\\  \\ \\_\\ \\_\\     \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n");
    printf("  \\/_/  \\/_/   \\/_____/      \\/_____/   \\/_____/   \\/_/     \\/_____/   \\/_/ /_/      \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/ \n");
    printf("%s\n", LINES);
}

void print_name()
{
    char hostname[NAME_LENGTH];
    char cwd[NAME_LENGTH];
    getcwd(cwd, sizeof(cwd));

    char *last_dir = strrchr(cwd, '/');
    if (last_dir != NULL)
    {
        last_dir++; 
    }

    gethostname(hostname, sizeof(hostname));

    if(strcmp(getlogin(), last_dir) != 0)
        printf(BOLD YELLOW"%s"WHITE"@"RED"%s"" "BLUE"%s/", getlogin(), hostname, last_dir);
    else
        printf(BOLD YELLOW"%s"WHITE"@"RED"%s"" "BLUE"~", getlogin(), hostname);

    printf(RESET" $ ");
}

void get_command(char * command)
{
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = '\0';
}

void deal_command(char * command)
{
    char *args[MAX_COMMAND_LENGTH];
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL) 
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if(strcmp(args[0], "cd") == 0)
    {
        my_cd(args);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) 
    {
        // 子进程
        execvp(args[0], args);

        printf("无效命令：%s\n", args[0]);
        exit(EXIT_FAILURE);
    } 
    else if (pid > 0) 
    {
        // 父进程
        wait(NULL);  // 等待子进程结束
    } 
    else 
    {
        printf("无法创建子进程\n");
    }
}

void my_cd(char ** args)
{
    int i = 0;
    while (args[i] != NULL)
    {
        if (i > 1)
        {
            printf("cd: 参数太多了!\n");
            return;
        }
        i++;
    }

    char current_dir[NAME_LENGTH];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        printf("cd: 无法获取当前目录\n");
        return;
    }

    if(args[1] == NULL)
    {
        char *home_dir = getenv("HOME");
        if (home_dir != NULL)
        {
            if (chdir(home_dir) == -1)
            {
                printf("cd: 无法进入目录 '%s'\n", home_dir);
                return;
            }
        }
        else
        {
            printf("cd: 无法找到家目录\n");
            return;
        } 

        setenv("OLDPWD", current_dir, 1);
        return;
    }

    if (strcmp(args[1], "-") == 0)
    {
        char *previous_dir = getenv("OLDPWD");
        if (previous_dir != NULL)
        {


            if (chdir(previous_dir) == -1)
            {
                printf("cd: 无法进入目录 '%s'\n", previous_dir);
                return;
            }

        }
        else
        {
            printf("cd: 无法找到上一个工作目录\n");
            return;
        }
    }
    else
    {
        if (chdir(args[1]) == -1)
        {
            printf("cd: 无法进入目录 '%s'\n", args[1]);
            return;
        }
    }

        setenv("OLDPWD", current_dir, 1); // 更新上一个工作目录
}
