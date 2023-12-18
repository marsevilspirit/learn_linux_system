#include "myshell.h"

void disable_EOF() 
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_cc[VEOF] = _POSIX_VDISABLE;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

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

    printf(BOLD YELLOW"%s"WHITE"@"RED"%s"" "BLUE"%s/", getlogin(), hostname, (strcmp(getlogin(), last_dir)?last_dir:"~"));

    printf(RESET" $ ");

    fflush(stdout);
}

void get_command(char * command)
{
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = '\0';
}

void deal_command(char * command)
{
    char dir[15];
    sprintf(dir, "/home/%s",getlogin());

    char *args[MAX_COMMAND_LENGTH];
    int cnt = 0;
    char *token = strtok(command, MYSH_TOKEN);
    while (token != NULL) 
    {
        args[cnt] = token;
        token = strtok(NULL, MYSH_TOKEN);
        if(strcmp(args[cnt], "~") == 0)
        {
            args[cnt] = dir;
        }
        cnt++;
    }
    args[cnt] = NULL;

    if(args[0] == NULL)
    {
        return;
    }

    if(strcmp(args[0], "cd") == 0)
    {
        my_cd(args);
        return;
    }

    execute(args, cnt);
}

void execute(char **args, int cnt)
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        printf("无法创建子进程");
    }

    if (pid == 0)
    {
        deal_pipe(0, cnt, args);
        return;
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
}

void deal_pipe(int left, int right, char **args)
{
    int flag_pipe = -1;

    for (int i = left; i < right; i++)
    {
        if (strcmp(args[i], "|") == 0) 
        {
            flag_pipe = i;
            break;
        }
    }

    if (flag_pipe == -1) 
    {
        deal_others(left, right, args);
        return;
    }

    if (flag_pipe + 1 == right)
    {
        printf("|后面缺少参数\n");
        return;
    }

    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");    
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("无法创键子进程");
    }

    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        deal_others(left, flag_pipe, args);
        exit(0);
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);

        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        deal_pipe(flag_pipe + 1, right, args);
    }
}

void deal_others(int left, int right, char **args)
{
    int fd;
    int is_background = 0;

    if (!find(args[left]))
    {
        return;
    }

    for (int i = left; i < right; i++)
    {
        if (strcmp(args[i], "&") == 0)
        {
            is_background = 1;
            args[i] = NULL;
            break;
        }
    }

    for (int i = left; i < right; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            fd = open(args[i + 1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
            i++;
        }
        if (strcmp(args[i], ">") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            i++;
        }
        if (strcmp(args[i], ">>") == 0)
        {
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            i++;
        }
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        printf("无法创建子进程");
    }

    if (pid == 0)
    {
        char *command[MAX_COMMAND_LENGTH];
        for (int i = left; i < right; i++)
        {
            command[i] = args[i];
        }
        command[right] = NULL; 
        execvp(command[left], command + left);
    }
    else if (pid > 0)
    {
        if (is_background == 0)
        {
            waitpid(pid, NULL, 0);
        }
    }
}

int find(char *command)
{
    DIR *dir;
    struct dirent *sdp;
    char *path[] = {"/bin", "/usr/bin", "./", NULL};

    if (strncmp(command, "./", 2) == 0) 
    {
        command = command + 2; 
    }

    for (int i = 0; path[i] != NULL; i++)
    {
        dir = opendir(path[i]);
        while ((sdp = readdir(dir)) != NULL)
        {
            if (strcmp(command, sdp->d_name) == 0)
            {
                closedir(dir);
                return 1;
            }
        }
    }

    closedir(dir);
    return 0;
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

    setenv("OLDPWD", current_dir, 1); 
}
