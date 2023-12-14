#include "myshell.h"

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
}

void deal_command(char * command)
{
    pid_t pid = fork();
    if (pid == 0) 
    {
        // 子进程
        char *args[MAX_COMMAND_LENGTH];
        int i = 0;
        char *token = strtok(command, " \n");
        while (token != NULL) 
        {
            args[i++] = token;
            token = strtok(NULL, " \n");
        }
        args[i] = NULL;
        
        execvp(args[0], args);
        printf("无法执行命令：%s\n", args[0]);
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
