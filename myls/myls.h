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

#define BLUE    "\x1b[94m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[93m"
#define RESET   "\x1b[0m"
#define MAX_STACK_SIZE 1000
#define MAX_PATH_LENGTH 256

//show list
void judge_file(char * use_arg);

void file_list(char * use_arg);

void dir_list(char * use_arg); 

void list_name_sort(char ** list_name, int i, const char *dir_path);//按最后修改时间排序

void name_strcmp_sort(char **list_name, int len);//按字母顺序排序

void list_i(char *list_name,  const char *dir_path);

void list_s(char *list_name,  const char *dir_path);

void list_l(char *list_name,  const char *dir_path);

void list_R(DIR * dir, const char *dir_path);

void print_color(char * list_name, const char *dir_path);//打印颜色
