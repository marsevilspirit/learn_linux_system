#include "myls.h"
#include <dirent.h>
#include <stdio.h>

extern int optind, opterr, optopt;
extern char * optarg;
int flaga = 0;

int main(int argc, char *argv[])
{
    int opt, i = 0, j = 0; 
    DIR * dir;
    struct dirent * entry;
    char *arg[10];

    while(argv[i] == NULL)
    {
        if(argv[i][0] != '-')
        {
            arg[j] = argv[i];
            j++; 
        }
        i++;
    }

    if(argc < 2)
    {
        dir = opendir(".");
    }
    else
    {
    dir = opendir(argv[1]);
    }

    if(dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((opt = getopt(argc, argv, "alRtris")) != -1)
    {
        switch (opt)
        {
            case 'a':      
                flaga++;
                break;
            case 'l':
                printf("we use l\n");
                break;
            case 'R':
                printf("we use R\n");
                break;
            case 't':
                printf("we use t\n");
                break;
            case 'r':
                printf("we use r\n");
                break;
            case 'i':
                printf("we use i\n");
                break;
            case 's':
                printf("we use s\n");
                break;
            case '?':
                printf("------------please don't do this-------------\n");
                break;
        }     
    }    

    show_ls(dir, entry);

    closedir(dir);

    return 0;
}
