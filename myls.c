#include "myls.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int opt; 
    DIR * dir;
    struct dirent * entry;

    dir = opendir(argv[1]);
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
                printf("we use a\n");
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
        }     
    }    

    show_ls(dir, entry);

    closedir(dir);

    return 0;
}
