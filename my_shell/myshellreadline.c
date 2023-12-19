#include "myshell.h"

int main(void)
{
    print_myshell();

    char *command = (char *)malloc(MAX_COMMAND_LENGTH*sizeof(char));

    signal(SIGINT, SIG_IGN);

    while (TRUE) 
    {
        print_name();

        char *command = readline(NULL);
        if (command == NULL) 
        {
            break; // 处理 Ctrl+D（EOF）的情况
        }

        if (strlen(command) > 0) 
        {
            add_history(command); // 添加输入到历史记录中
            if (strcmp(command, "exit") == 0) 
            {
                free(command);
                break;
            }
            deal_command(command);
        }
        free(command);
    }

    return 0;
}
