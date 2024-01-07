#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 200

int main(void)
{
    char str[MAX_CMD_LEN];
    int status;

    for(;;)
    {
        printf("mars:$ ");
        fflush(stdout);
        if(fgets(str, MAX_CMD_LEN, stdin) == NULL)
            break;

        status = system(str);
        printf("system() returned: status=0x%04x (%d,%d)\n", (unsigned int)status, status >> 8, status & 0xff);

        if(status == -1)
        {
            perror("status");
            exit(EXIT_FAILURE);
        }
        else
        {
            if(WIFEXITED(status) && WEXITSTATUS(status) == 127)
                printf("(Probably) could not invoke shell\n");
        }
    } 
    exit(EXIT_SUCCESS);
}
