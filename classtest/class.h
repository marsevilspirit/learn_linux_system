#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <openssl/ssl.h>
#include <auth-client.h>
#include <libesmtp.h>
#include <time.h>
#include <regex.h>

#define MAX_USERS 100
#define MAX_USERMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define DATABASE_FILE "users.txt"
#define PATIENT_FILE "patient.txt"
#define LEN 30//姓名和病号的最大字符数 
#define N 50//最大病人人数

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define BLACK "\033[0;30m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"


typedef struct {
    char usermail[MAX_USERMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

struct patient
{
	char pat_ID[LEN]; 
	char pat_name[LEN];
	char pat_age[10];
	char pat_sex[10];
    char pat_disease[LEN];
    char pat_state[LEN];
};

//账号管理函数
void loadUsersFromFile();
void registerUser();
int loginUser();
void changePassword();
void forgotPassword();

//发送邮件函数
int verify(char* usermail, char* verify_number);

//病人函数
void menu();//主菜单函数 
void loadPatientFromFile();
void help();//使用帮助 
void savePatientToFile();//增加病人信息  
void searchPatient();//查找病人信息
void deletePatientByID();//删除病人信息 
void displayAllPatients();
void generatePersonnelList();
void modifyPatientByID();//修改病人信息   
void displayNotice();
void my_exit();//退出函数 
                        


