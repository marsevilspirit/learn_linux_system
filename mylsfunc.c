#include "myls.h"
#include <dirent.h>
#include <stdio.h>

extern int flaga; 

void show_ls(DIR * dir, struct dirent * entry)
{
    while ((entry = readdir(dir)) != NULL)
    {
        if(entry->d_name[0] == '.' && flaga ==0)
            continue;
        printf("%s\n", entry->d_name);
    }
}
