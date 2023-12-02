#include "myls.h"

extern int optind, opterr, optopt;
extern char * optarg;
int flag_a = 0;

int main(int argc, char *argv[])
{
    int opt, i = 1; 
    DIR * dir;
    struct dirent * entry;

    if(argc == 1)
        dir = opendir(".");
    else
    {
        while (argv[i] != NULL && argv[i][0] == '-')
            i++;         
        if(argv[i] == NULL)
            dir = opendir(".");
        else
            dir = opendir(argv[i]);
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
                flag_a++;
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

    list(dir, entry);

    closedir(dir);

    return 0;
}
