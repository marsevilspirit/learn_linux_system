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
    command[strcspn(command, "\n")] = '\0';
}

void deal_command(char * command)
{
    pid_t pid = fork();
    if (pid == 0) 
    {
        // 子进程
        char *args[MAX_COMMAND_LENGTH];
        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL) 
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        execvp(args[0], args);

        if(strcmp(args[0], "cd") == 0)
        {
            if (args[1] != NULL)
            {
                if (strcmp(args[1], "-") == 0)
                {
                    char *previous_dir = getenv("OLDPWD");
                    if (previous_dir != NULL)
                    {
                        if (chdir(previous_dir) == -1)
                        {
                            printf("cd: 无法进入目录 '%s'\n", previous_dir);
                        }
                    }
                    else
                    {
                        printf("cd: 无法找到上一个工作目录\n");
                    }
                }
                else
                {
                    if (chdir(args[1]) == -1)
                    {
                        printf("cd: 无法进入目录 '%s'\n", args[1]);
                    }
                }
            }
            else
            {
                char *home_dir = getenv("HOME");
                if (home_dir != NULL)
                {
                    if (chdir(home_dir) == -1)
                    {
                        printf("cd: 无法进入目录 '%s'\n", home_dir);
                    }
                }
                else
                {
                    printf("cd: 无法找到家目录\n");
                }            
            }

            return 0;
        }

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
