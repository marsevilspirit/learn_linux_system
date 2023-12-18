#include "myshell.h"

void disable_eof() 
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_cc[VEOF] = _POSIX_VDISABLE;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main(void)
{
    print_myshell();

    char *command = (char *)malloc(MAX_COMMAND_LENGTH*sizeof(char));

    signal(SIGINT, SIG_IGN);
    disable_eof();

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
