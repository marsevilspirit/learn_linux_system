#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1
#define MAX_COMMAND_LENGTH 100
#define NAME_LENGTH 256
#define MYSH_TOKEN " \t\r\n"
#define LINES "========================================================================================================================================="

#define RESET       "\x1B[0m"
#define RED         "\x1B[31m"
#define YELLOW      "\x1B[33m"
#define BLUE        "\x1B[34m"
#define WHITE       "\x1B[37m"
#define BOLD        "\033[1m"

void disable_EOF();

void print_myshell();

void print_name();

void get_command(char * command);

void deal_command(char * command);

void execute(char ** args, int cnt);

void deal_pipe(int left, int right, char ** args);

void deal_others(int left, int right, char ** args);

void my_cd(char ** args);
