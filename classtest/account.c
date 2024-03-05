#include "class.h"
 
User users[MAX_USERS];
int numUsers = 0;

void loadUsersFromFile() 
{
    FILE *file = fopen(DATABASE_FILE, "r");
    if (file == NULL)
    {
        printf("数据文件没找到\n");
        return;
    }
    while (fscanf(file, "%s %s", users[numUsers].usermail, users[numUsers].password) != EOF) //加载文件中的用户信息
    {
        numUsers++;
    }
    fclose(file);
}

static void saveUsersToFile() 
{
    FILE *file = fopen(DATABASE_FILE, "w");
    if (file == NULL) 
    {
        printf("无法写入文件\n");
        return;
    }
    for (int i = 0; i < numUsers; i++) 
    {
        fprintf(file, "%s %s\n", users[i].usermail, users[i].password);
    }
    fclose(file);
}

static int isUsernameTaken(const char *usermail) 
{
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].usermail, usermail) == 0) 
        {
            return 1; //用户存在 
        }
    }
    return 0; //用户不存在 
}

// 函数用于检查字符串是否符合邮箱格式
static int is_valid_email(const char *email) 
{
    regex_t regex;
    int reti;

    // 正则表达式，匹配常见的邮箱格式
    char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";

    // 编译正则表达式
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) 
    {
        fprintf(stderr, "无法编译reti\n");
        exit(1);
    }

    // 执行正则表达式匹配
    reti = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (!reti) 
    {
        return 1; // 匹配成功，字符串符合邮箱格式
    } else {
        return 0; // 匹配失败，字符串不符合邮箱格式
    }
}

void registerUser() 
{
    char usermail[MAX_USERMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("输入邮箱: ");
    scanf("%s", usermail);

    if(!is_valid_email(usermail))
    {
        printf("请输入正确的邮箱");
        return;
    }

    if (isUsernameTaken(usermail)) 
    {
        printf("该邮箱已注册\n");
        return;
    }

        static char verify_number[5]; // 用于存储结果的字符数组，包括最后一个位置用于'\0'
        srand(time(NULL)); // 设置随机数种子为当前时间
        int random_number = rand() % 9000 + 1000; // 生成1000到9999之间的随机数
        sprintf(verify_number, "%d", random_number); // 将随机数转换为字符串形式

        if(verify(usermail, verify_number))
        {
            printf("\n\n\n\n\t\t验证码发送失败"); 
            return;
        }
        else
        {
            printf("\n\n\n\n\t\t已向你的邮箱发送验证码");
        } 

        char temp_number[5];
        printf("\n\t\t请输入验证码:");
        scanf("%s", temp_number);

        if(strcmp(temp_number, verify_number) != 0)
        {
            printf("\t\t验证失败\n");
            return;
        }
        else 
        {
            printf("\t\t验证成功\n");
        }

    printf("输入密码: ");
    scanf("%s", password);

    if (numUsers < MAX_USERS) 
    {
        strcpy(users[numUsers].usermail, usermail);
        strcpy(users[numUsers].password, password);
        numUsers++;
        saveUsersToFile();
        printf("注册成功\n");
    } 
    else 
    {
        printf("已达到最大用户数量，无法注册\n");
    }
}

int loginUser() 
{
    char usermail[MAX_USERMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("输入邮箱: ");
    scanf("%s", usermail);
    printf("输入密码: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) 
    {
        if (strcmp(users[i].usermail, usermail) == 0 && strcmp(users[i].password, password) == 0) 
        {
            printf("登入成功\n");
            return 1;
        }
    }
    printf("邮箱与密码不匹配\n");
    return 0;
}

void changePassword() 
{
    char usermail[MAX_USERMAIL_LENGTH];
    char oldPassword[MAX_PASSWORD_LENGTH];
    char newPassword[MAX_PASSWORD_LENGTH];

    printf("输入邮箱: ");
    scanf("%s", usermail);
    printf("输入旧密码: ");
    scanf("%s", oldPassword);

    for (int i = 0; i < numUsers; i++) 
    {
        if (strcmp(users[i].usermail, usermail) == 0 && strcmp(users[i].password, oldPassword) == 0) 
        {
            printf("输入新的密码: ");
            scanf("%s", newPassword);
            strcpy(users[i].password, newPassword);
            saveUsersToFile();
            printf("密码修改成功\n");
            return;
        }
    }
    printf("无效的邮箱或密码\n");
}

void forgotPassword() 
{
    char usermail[MAX_USERMAIL_LENGTH];

    printf("输入邮箱: "); 
    scanf("%s", usermail);

    for (int i = 0; i < numUsers; i++) 
    {
        if (strcmp(users[i].usermail, usermail) == 0) 
        {
            static char verify_number[5]; // 用于存储结果的字符数组，包括最后一个位置用于'\0'
            srand(time(NULL)); // 设置随机数种子为当前时间
            int random_number = rand() % 9000 + 1000; // 生成1000到9999之间的随机数
            sprintf(verify_number, "%d", random_number); // 将随机数转换为字符串形式

            if(verify(usermail, verify_number))
            {
                printf("\n\n\n\n\t\t验证码发送失败\n"); 
            }
            else
            {
                printf("\n\n\n\n\t\t已向你的邮箱发送验证码\n");
            } 

            char temp_number[5];
            printf("\n\t\t请输入验证码:");
            scanf("%s", temp_number);

            if(strcmp(temp_number, verify_number) == 0)
            {
                printf("\t\t你的密码是：%s\n", users[i].password);
            }
            else
            {
                printf("验证失败\n"); 
            }

            return;
        }
    }
    printf("该邮箱未注册\n");
}
