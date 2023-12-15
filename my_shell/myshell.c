#include "myshell.h"

int main(void)
{
    print_myshell();
    while (TRUE) 
    {
        char *command = (char *)malloc(MAX_COMMAND_LENGTH*sizeof(char));
        print_name();
        get_command(command); 
        if(strcmp(command, "exit") == 0)
        {
            free(command);
            exit(EXIT_SUCCESS);
        }
        deal_command(command);
        free(command);
    }
    return 0;
}
