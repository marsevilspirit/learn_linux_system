#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
 
//show list
void judge_file(char * use_arg);

void file_list(char * use_arg);

void dir_list(char * use_arg); 

void list_name_sort(struct dirent ** list_name, int i);

