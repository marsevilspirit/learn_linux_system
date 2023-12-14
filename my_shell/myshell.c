#include "myshell.h"

int main(void)
{
    while (TRUE) 
    {
        char *command = (char *)malloc(MAX_COMMAND_LENGTH*sizeof(char));
        print_name();
        get_command(command); 
        if(strcmp(command, "exit") == 0)
        {
            exit(EXIT_FAILURE);
        }
        deal_command(command);
        free(command);
    }
    return 0;
}
