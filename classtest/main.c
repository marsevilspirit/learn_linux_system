#include "class.h"

int main(void)
{
    loadUsersFromFile();

    system("clear");

    printf("\n\n\n\n\t\t正在进入系统\n");
    printf("\t\t加载中:[");
    for(int i = 0; i <8; i++)
    {
        printf("#######");
        usleep(300000);
        fflush(stdout);
    } 
    printf("]\n");
    printf("\n\n\t\t加载成功");
    fflush(stdout);

    sleep(1);

    int choice_1;
    do {
        system("clear");

        printf("\t\t\t\t                                                     \n");
        printf("\t\t\t\t-----------------------------------------------------\n");
        printf("\t\t\t\t|            "RED"精"YELLOW"神"GREEN"病"BLUE"院"RESET"内部人员管理系统               |\n");
        printf("\t\t\t\t|                                                   |\n");
        printf("\t\t\t\t|                     登陆界面                      |\n");
        printf("\t\t\t\t-----------------------------------------------------\n");
        printf("\t\t\t\t|                                                   |\n");
        printf("\t\t\t\t|     1、注册                 2、登录               |\n");
        printf("\t\t\t\t|                                                   |\n");
        printf("\t\t\t\t|     3、修改密码             4、忘记密码           |\n");
        printf("\t\t\t\t|                                                   |\n");
        printf("\t\t\t\t|     5、退出程序                                   |\n");
        printf("\t\t\t\t|                                                   |\n");
        printf("\t\t\t\t-----------------------------------------------------\n");

        printf("\n\t\t\t输入选项：");

        if (scanf("%d", &choice_1) != 1)
        {
            // 清空输入缓冲区中的无效字符
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("\t\t\t无效选项\n");
            usleep(50000);
            continue;
        }

        switch (choice_1) 
        {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser()) 
                {
                    goto _menu; 
                }
                break;
            case 3:
                changePassword();
                break;
            case 4:
                forgotPassword();
                break;
            case 5:
                printf("退出中...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("无效选项\n");
        }

        sleep(1);
    } while (choice_1 != 5);

_menu:
    system("clear");

    loadPatientFromFile(); 

    int choice_2;
    do {
        system("clear");

        menu();
        printf("\n\t\t\t输入选项：");

        if (scanf("%d", &choice_2) != 1)
        {
            // 清空输入缓冲区中的无效字符
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("无效选项\n");
            usleep(50000);
            continue;
        }

        switch (choice_2) {
            case 1:
                help();
                break;
            case 2:
                savePatientToFile();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                deletePatientByID();
                break;
            case 5:
                modifyPatientByID();
                break;
            case 6:
                displayAllPatients();
                break;
            case 7:
                generatePersonnelList();
                break;
            case 8:
                displayNotice();
                break;
            case 9:
                my_exit();
                break;
            default:
                printf("无效选项\n");
                break;
        }

        usleep(50000);
    } while (choice_2 != 9);

    return 0;
}

