#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define MAX_COMMAND_LENGTH 100

#define RESET       "\x1B[0m"
#define RED         "\x1B[31m"
#define YELLOW      "\x1B[33m"
#define BLUE        "\x1B[34m"
#define WHITE       "\x1B[37m"

#define BRESET       "\033[0m"
#define BOLD        "\033[1m"

void print_name();

void get_command();
