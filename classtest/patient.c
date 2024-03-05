#include "class.h"

struct patient Pat[N];
int number_pat = 0;

void menu()
{
	printf("\t\t\t\t                                                     \n");
	printf("\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t|                 病人信息管理系统                  |\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t|                   系统功能菜单                    |\n");
	printf("\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t|     1、使用帮助             2、录入病人信息       |\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t|     3、查询病人信息         4、删除病人信息       |\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t|     5、修改病人信息         6、显示当前信息       |\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t|     7、制作名单             8、公告               |\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t|     9、退出系统                                   |\n");
	printf("\t\t\t\t|                                                   |\n");
	printf("\t\t\t\t-----------------------------------------------------\n");

}

void loadPatientFromFile() 
{
    FILE *file = fopen(PATIENT_FILE, "r");
    if (file == NULL)
    {
        printf("数据文件没找到\n");
        return;
    }

    while (fscanf(file, "%s %s %s %s %s %s", Pat[number_pat].pat_ID, Pat[number_pat].pat_name, Pat[number_pat].pat_age, Pat[number_pat].pat_sex, Pat[number_pat].pat_disease, Pat[number_pat].pat_state) != EOF) //加载文件中的病人信息
    {
        number_pat++;
    }
    fclose(file);
}

void help() 
{
    system("clear");

	printf("\t\t\t\t                                                     \n");
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|%s%s                     使用帮助                      %s|\n", RED, BOLD, RESET);
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|%s                                                   %s|\n", YELLOW, RESET);
    printf("\t\t\t\t|%s   1. 显示了系统功能菜单及其功能说明。             %s|\n", GREEN, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", CYAN, RESET);
    printf("\t\t\t\t|%s   2. 用于向系统中添加新的病人信息。               %s|\n", BLUE, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", MAGENTA, RESET);
    printf("\t\t\t\t|%s   3. 允许用户根据不同条件查找病人。               %s|\n", WHITE, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", RED, RESET);
    printf("\t\t\t\t|%s   4. 允许用户删除系统中的病人信息。               %s|\n", YELLOW, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", GREEN, RESET);
    printf("\t\t\t\t|%s   5. 允许用户修改系统中的病人信息。               %s|\n", CYAN, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", BLUE, RESET);
    printf("\t\t\t\t|%s   6. 允许用户查看系统中所有的病人信息。           %s|\n", MAGENTA, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", WHITE, RESET);
    printf("\t\t\t\t|%s   7. 制作该系统的人员名单。                       %s|\n", RED, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", YELLOW, RESET);
    printf("\t\t\t\t|%s   8. 允许用户查看系统发布的重要信息。             %s|\n", GREEN, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", CYAN, RESET);
    printf("\t\t\t\t|%s   9. 用于退出病人信息管理系统。                   %s|\n", BLUE, RESET);
    printf("\t\t\t\t|%s                                                   %s|\n", MAGENTA, RESET);
    printf("\t\t\t\t-----------------------------------------------------\n");


    printf("按回车退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}

void savePatientToFile() 
{
    FILE *file = fopen(PATIENT_FILE, "a");
    if (file == NULL) 
    {
        printf("无法写入文件\n");
        return;
    }

    char newID[20];
    // 循环直到用户输入一个不存在的 ID 或者输入 0 退出
    while (1) 
    {
        printf("当前可输入病号:%d\n", number_pat+1);       
        printf("病号(输入0退出): ");
        scanf("%s", newID);

        // 如果用户输入 0，则退出添加
        if (strcmp(newID, "0") == 0) 
        {
            fclose(file); // 关闭文件
            return;
        }

        int found = 0;
        // 检查新输入的 ID 是否已经存在于数组中
        for (int i = 0; i < number_pat; i++) 
        {
            if (strcmp(Pat[i].pat_ID, newID) == 0) 
            {
                printf("该病号已经存在，请重新输入。\n");
                found = 1;
                break;
            }
        }
        // 如果 ID 不存在于数组中，则跳出循环
        if (!found) 
        {
            break;
        }
    }
    
    strcpy(Pat[number_pat].pat_ID,newID);
    printf("\t\t姓名: ");
    scanf("%s", Pat[number_pat].pat_name);
    printf("\t\t年龄: ");
    scanf("%s", Pat[number_pat].pat_age);
    printf("\t\t性别: ");
    scanf("%s", Pat[number_pat].pat_sex);
    printf("\t\t病症: ");
    scanf("%s", Pat[number_pat].pat_disease);
    printf("\t\t状态: ");
    scanf("%s", Pat[number_pat].pat_state);

    // 将新病人信息写入文件
    fprintf(file, "%s %s %s %s %s %s\n", Pat[number_pat].pat_ID, Pat[number_pat].pat_name, Pat[number_pat].pat_age, Pat[number_pat].pat_sex, Pat[number_pat].pat_disease, Pat[number_pat].pat_state);   
    number_pat++;
    
    fclose(file);
}


void searchPatient() 
{
    int choice;
    printf("\t\t1. 按病号查询\n");
    printf("\t\t2. 按姓名查询\n");
    printf("\t\t请选择查询方式：");
    scanf("%d", &choice);

    if (choice == 1) 
    {
        char targetID[20];
        printf("\t\t请输入要查询的病人病号：");
        scanf("%s", targetID);

        int found = 0;
        for (int i = 0; i < number_pat; i++) 
        {
            if (strcmp(Pat[i].pat_ID, targetID) == 0) 
            {
                printf("\t\t病人信息：\n");
                printf("\t\t病号: %s\n", Pat[i].pat_ID);
                printf("\t\t姓名: %s\n", Pat[i].pat_name);
                printf("\t\t年龄: %s\n", Pat[i].pat_age);
                printf("\t\t性别: %s\n", Pat[i].pat_sex);
                printf("\t\t病症: %s\n", Pat[i].pat_disease);
                printf("\t\t状态: %s\n", Pat[i].pat_state);
                found = 1;
                break;
            }
        }

        if (!found) 
        {
            printf("未找到匹配的病人信息。\n");
        }
    } 
    else if (choice == 2) 
    {
        char targetName[50];
        printf("请输入要查询的病人姓名：");
        scanf("%s", targetName);

        int found = 0;
        for (int i = 0; i < number_pat; i++) 
        {
            if (strcmp(Pat[i].pat_name, targetName) == 0) 
            {
                printf("\t\t病人信息：\n");
                printf("\t\t病号: %s\n", Pat[i].pat_ID);
                printf("\t\t姓名: %s\n", Pat[i].pat_name);
                printf("\t\t年龄: %s\n", Pat[i].pat_age);
                printf("\t\t性别: %s\n", Pat[i].pat_sex);
                printf("\t\t病症: %s\n", Pat[i].pat_disease);
                printf("\t\t状态: %s\n", Pat[i].pat_state);
                found = 1;
            }
        }

        if (!found) 
        {
            printf("未找到匹配的病人信息。\n");
        }
    } 
    else 
    {
        printf("无效的选择。\n");
    }

    printf("按回车键退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}


void deletePatientByID() 
{
    char targetID[20];
    printf("请输入要删除的病人ID(输入0退出)：");
    scanf("%s", targetID);

            // 如果用户输入 0，则退出添加
        if (strcmp(targetID, "0") == 0) 
        {
            return;
        }

    int found = 0;
    for (int i = 0; i < number_pat; i++) 
    {
        if (strcmp(Pat[i].pat_ID, targetID) == 0) 
        {
            if (i == number_pat - 1) // 如果要删除的病人恰好是最后一个病人
            {
                // 直接减少病人数量即可
                number_pat--;
                printf("成功删除病人信息。\n");
            }
            else
            {
                // 将要删除的病人信息覆盖为数组中最后一个病人的信息
                strcpy(Pat[i].pat_ID, Pat[number_pat - 1].pat_ID);
                strcpy(Pat[i].pat_name, Pat[number_pat - 1].pat_name);
                strcpy(Pat[i].pat_age, Pat[number_pat - 1].pat_age);
                strcpy(Pat[i].pat_sex, Pat[number_pat - 1].pat_sex);
                strcpy(Pat[i].pat_disease, Pat[number_pat - 1].pat_disease);
                strcpy(Pat[i].pat_state, Pat[number_pat - 1].pat_state);

                // 减少病人数量
                number_pat--;

                printf("成功删除病人信息。\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("未找到匹配的病人信息。\n");
    }

    // 同步到文件中
    FILE *file = fopen(PATIENT_FILE, "w");
    if (file == NULL) 
    {
        printf("无法写入文件\n");
        return;
    }

    for (int i = 0; i < number_pat; i++) 
    {
        fprintf(file, "%s %s %s %s %s %s\n", Pat[i].pat_ID, Pat[i].pat_name, Pat[i].pat_age, Pat[i].pat_sex, Pat[i].pat_disease, Pat[i].pat_state);
    }
    fclose(file);

    printf("按回车键退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}

void modifyPatientByID() 
{
    char targetID[20];
    printf("请输入要修改的病人ID：");
    scanf("%s", targetID);

    int found = 0;
    for (int i = 0; i < number_pat; i++) 
    {
        if (strcmp(Pat[i].pat_ID, targetID) == 0) 
        {
            printf("\t\t病人信息：\n");
            printf("\t\t病号: %s\n", Pat[i].pat_ID);
            printf("\t\t姓名: %s\n", Pat[i].pat_name);
            printf("\t\t年龄: %s\n", Pat[i].pat_age);
            printf("\t\t性别: %s\n", Pat[i].pat_sex);
            printf("\t\t病症: %s\n", Pat[i].pat_disease);
            printf("\t\t状态: %s\n", Pat[i].pat_state);

            printf("请输入新的病人信息：\n");
            printf("\t\t姓名: ");
            scanf("%s", Pat[i].pat_name);
            printf("\t\t年龄: ");
            scanf("%s", Pat[i].pat_age);
            printf("\t\t性别: ");
            scanf("%s", Pat[i].pat_sex);
            printf("\t\t病症: ");
            scanf("%s", Pat[i].pat_disease);
            printf("\t\t状态: ");
            scanf("%s", Pat[i].pat_state);

            printf("\t\t成功修改病人信息。\n");

            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("\t\t未找到匹配的病人信息。\n");
    }

    // 同步到文件中
    FILE *file = fopen(PATIENT_FILE, "w");
    if (file == NULL) 
    {
        printf("无法写入文件\n");
        return;
    }

    for (int i = 0; i < number_pat; i++) 
    {
        fprintf(file, "%s %s %s %s %s %s\n", Pat[i].pat_ID, Pat[i].pat_name, Pat[i].pat_age, Pat[i].pat_sex, Pat[i].pat_disease, Pat[i].pat_state);
    }
    fclose(file);

    printf("按回车键退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}

// 归并函数，用于合并两个已排序的子数组
void mergeID(struct patient arr[], int l, int m, int r, int ascending) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // 创建临时数组
    struct patient L[n1], R[n2];

    // 拷贝数据到临时数组 L[] 和 R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // 归并临时数组到 arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if ((ascending && strcmp(L[i].pat_ID, R[j].pat_ID) <= 0) || (!ascending && strcmp(L[i].pat_ID, R[j].pat_ID) >= 0)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 将剩余元素拷贝到 arr[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序函数
void mergeIDSort(struct patient arr[], int l, int r, int ascending) {
    if (l < r) {
        // 求中间位置
        int m = l + (r - l) / 2;

        // 分割数组
        mergeIDSort(arr, l, m, ascending);
        mergeIDSort(arr, m + 1, r, ascending);

        // 合并已排序的子数组
        mergeID(arr, l, m, r, ascending);
    }
}

// 归并函数，用于合并两个已排序的子数组
void mergeAge(struct patient arr[], int l, int m, int r, int ascending) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // 创建临时数组
    struct patient L[n1], R[n2];

    // 拷贝数据到临时数组 L[] 和 R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // 归并临时数组到 arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if ((ascending && strcmp(L[i].pat_age, R[j].pat_age) <= 0) || (!ascending && strcmp(L[i].pat_age, R[j].pat_age) >= 0)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // 将剩余元素拷贝到 arr[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序函数
void mergeAgeSort(struct patient arr[], int l, int r, int ascending) {
    if (l < r) {
        // 求中间位置
        int m = l + (r - l) / 2;

        // 分割数组
        mergeAgeSort(arr, l, m, ascending);
        mergeAgeSort(arr, m + 1, r, ascending);

        // 合并已排序的子数组
        mergeAge(arr, l, m, r, ascending);
    }
}

void displayAllPatients() 
{
    if (number_pat == 0) 
    {
        printf("没有病人信息可显示。\n");
        return;
    }

    char temp[10] = "0";
    printf("病号顺序请按1, 年龄顺序请按2: ");
    scanf("%s", temp);

    int ascending = 1; // 默认升序
    printf("升序请按1，降序请按0: ");
    scanf("%d", &ascending);

    if(strcmp(temp, "1") == 0)
        mergeIDSort(Pat, 0, number_pat - 1, ascending);
    else if(strcmp(temp, "2") == 0)
        mergeAgeSort(Pat, 0, number_pat - 1, ascending);

    printf("所有病人信息：\n");
    printf("\t\t病号      姓名             年龄      性别        病症              状态\n");
    for (int i = 0; i < number_pat; i++) 
    {
        printf("\t\t%-9s%-22s%-10s%-11s%-22s%s\n", Pat[i].pat_ID, Pat[i].pat_name, Pat[i].pat_age, Pat[i].pat_sex, Pat[i].pat_disease, Pat[i].pat_state);
    }

    printf("按回车键退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}



void generatePersonnelList() {
    system("clear"); 

	printf("\t\t\t\t                                                     \n");
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|                    %s制作人员名单%s                   |\n", CYAN, RESET);
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   系统设计：%s方泽亚%s                                |\n", BLUE, RESET);
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   程序编写：%s方泽亚%s                                |\n", BLUE, RESET);
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   测试调试：%s方泽亚%s                                |\n", BLUE, RESET);
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   技术支持：%s方泽亚%s                                |\n", BLUE, RESET);
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   联系方式：%s15643870618%s                           |\n", MAGENTA, RESET);
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t-----------------------------------------------------\n");


    printf("按任意键退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}

void displayNotice() 
{
    system("clear");

	printf("\t\t\t\t                                                     \n");
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|                  %s精神病院内部人员公告%s             |\n", RED, RESET);
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   尊敬的医护人员，                                |\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   我们收到了一份紧急通知，一名危险病人从病房逃离。|\n");
    printf("\t\t\t\t|   病人名%s阿萨德%s，性别男，年龄30岁，患有精神分裂症。|\n", RED, RESET);
    printf("\t\t\t\t|   请大家加强警戒，协助安保部门查找并防止其逃逸。  |\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   如果您发现该病人的行踪，请立即联系安保部门。    |\n");
    printf("\t\t\t\t|   为了保障医院安全，请全体人员做好安全防范措施。  |\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   祝大家平安！                                    |\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t-----------------------------------------------------\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t|   本系统将于%s下周一%s进行维护，                      |\n", RED, RESET);
    printf("\t\t\t\t|   预计维护时间为%s3小时%s。                           |\n", RED, RESET);
    printf("\t\t\t\t|   维护期间，系统将无法访问。                      |\n");
    printf("\t\t\t\t|   感谢您的理解与配合。                            |\n");
    printf("\t\t\t\t|                                                   |\n");
    printf("\t\t\t\t-----------------------------------------------------\n");


    printf("按任意键退出\n");
    getchar(); // 清空输入缓冲区
    getchar(); // 等待用户按下任意键
}


void my_exit()
{
    printf("退出中...\n");
    exit(EXIT_SUCCESS);
}
