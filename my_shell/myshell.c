#include "myshell.h"

int main(void)
{
    print_myshell();

    char *command = (char *)malloc(MAX_COMMAND_LENGTH*sizeof(char));

    while (TRUE) 
    {
        print_name();
        get_command(command); 
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        deal_command(command);
    }
            
    free(command);

    return 0;
}
