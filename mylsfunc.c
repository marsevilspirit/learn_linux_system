#include "myls.h"
#include <dirent.h>
#include <stdio.h>

void show_ls(DIR * dir, struct dirent * entry)
{
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s  ", entry->d_name);
    }
    printf("\n");
}
