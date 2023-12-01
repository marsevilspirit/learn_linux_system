#include "myls.h"

int main(int argc, char *argv[])
{
    DIR * dir;
    struct dirent * entry;

    dir = opendir(argv[1]);
    if(dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    show_ls(dir, entry);

    closedir(dir);

    return 0;
}
