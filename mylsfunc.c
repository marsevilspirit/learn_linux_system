#include "myls.h"

extern int flag_a; 

void list(DIR * dir, struct dirent * entry)
{
    while ((entry = readdir(dir)) != NULL)
    {
        if(entry->d_name[0] == '.' && flag_a ==0)
            continue;
        printf("%s\n", entry->d_name);
    }
}
