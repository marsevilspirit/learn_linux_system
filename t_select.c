#include <sys/time.h>
#include <sys/select.h>
#include "tlpi_hdr.h"

static void 
usageError(const char* progName)
{
    fprintf(stderr, "Usage: %s {timeout|-} fd-num[rw]...\n", progName);
    fprintf(stderr, "    - means infinite timeout;\n");
    fprintf(stderr, "    r = monitor for read\n");
    fprintf(stderr, "    w = monitor for write\n");
    fprintf(stderr, "    e.g.: %s - Orw 1w\n", progName);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    fd_set readfds, writefds;
    int ready, nfds, fd, numRead, j;
    struct timeval timeout;
    struct timeval* pto;
    char buf[10];

    if(argc < 2 || strcmp(argv[1], "--help") == 0)
        usageError(argv[0]);
    else 
    {
        pto = &timeout;
        timeout.tv_sec = getLong(argv[1], 0, "timeout");
        timeout.tv_usec = 0;
    }

    nfds = 0;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);

    for(j = 2; j < argc; j++)
    {
        numRead = sscanf(argv[j], "%d%3[rw]", &fd, buf);
        if(numRead != 2)
            usageError(argv[0]);
        if(fd >= FD_SETSIZE)
            cmdLineErr("file");
    }
}

