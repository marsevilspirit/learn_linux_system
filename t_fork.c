#include "tlpi_hdr.h"

static int idata = 111;

int main(int argc, char * argv[])
{
    int istack = 222;
    pid_t childPid;

    switch (childPid = fork())
    {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        
        case 0:
            idata *= 3;
            istack *= 3;
            break;

        default:
            sleep(3);
            break;
    }

    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), (childPid == 0)?"(child) ": "(parent)", idata, istack);

    exit(EXIT_SUCCESS);
}
