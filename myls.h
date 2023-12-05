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

typedef struct {
    char path[MAX_PATH_LENGTH];
    int index;
} StackEntry;

typedef struct {
    StackEntry entries[MAX_STACK_SIZE];
    int top;
} Stack;

void stack_init(Stack* stack);

int stack_empty(Stack* stack);

int stack_full(Stack* stack);

void stack_push(Stack* stack, const char* path, int index);

void stack_pop(Stack* stack, char* path, int* index);


//show list
void judge_file(char * use_arg);

void file_list(char * use_arg);

void dir_list(char * use_arg); 

void list_name_sort(struct dirent ** list_name, int i, const char *dir_path);//按最后修改时间排序

void name_strcmp_sort(struct dirent **list_name, int len);//按字母顺序排序

void list_i(struct dirent *list_name,  const char *dir_path);

void list_s(struct dirent *list_name,  const char *dir_path);

void list_l(struct dirent *list_name,  const char *dir_path);

void list_R(DIR * dir, const char *dir_path);

void print_color(struct dirent * list_name, const char *dir_path);//打印颜色
