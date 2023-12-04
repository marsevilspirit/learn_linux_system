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
#include <string.h>

#define BLUE    "\x1b[34m"
#define GREEN   "\x1b[32m"

//show list
void judge_file(char * use_arg);

void file_list(char * use_arg);

void dir_list(char * use_arg); 

void list_name_sort(struct dirent ** list_name, int i, const char *dir_path);//按最后修改时间排序

void name_strcmp_sort(struct dirent **list_name, int len);//按字母顺序排序

void list_l(struct dirent **list_name);

void print_color(struct dirent ** list_name);
