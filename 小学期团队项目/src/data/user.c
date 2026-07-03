#include "user.h"

// 全局变量
User* userHead = NULL;
User* loginUser = NULL;

// ==================== 基础链表操作 ====================
User* createUserNode(char* uid, char* name, char* pwd, char* phone, char* desc)
{
    User* newNode = (User*)malloc(sizeof(User));
    if (newNode == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    strncpy(newNode->uid, uid, UID_LEN - 1);
    newNode->uid[UID_LEN - 1] = '\0';

    strncpy(newNode->username, name, USER_NAME_LEN - 1);
    newNode->username[USER_NAME_LEN - 1] = '\0';

    strncpy(newNode->password, pwd, PWD_LEN - 1);
    newNode->password[PWD_LEN - 1] = '\0';

    strncpy(newNode->phone, phone, PHONE_LEN - 1);
    newNode->phone[PHONE_LEN - 1] = '\0';

    strncpy(newNode->desc, desc, DESC_LEN - 1);
    newNode->desc[DESC_LEN - 1] = '\0';

    newNode->next = NULL;
    return newNode;
}

void addUser(User* newNode)
{
    if (newNode == NULL) return;
    if (userHead == NULL)
    {
        userHead = newNode;
        return;
    }
    User* p = userHead;
    while (p->next != NULL)
        p = p->next;
    p->next = newNode;
}

User* findUserByUid(char* uid)
{
    User* p = userHead;
    while (p != NULL)
    {
        if (strcmp(p->uid, uid) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void updateUser(User* target, char* newName, char* newPhone, char* newDesc)
{
    if (target == NULL) return;
    if (strlen(newName) > 0)
    {
        strncpy(target->username, newName, USER_NAME_LEN - 1);
        target->username[USER_NAME_LEN - 1] = '\0';
    }
    if (strlen(newPhone) > 0)
    {
        strncpy(target->phone, newPhone, PHONE_LEN - 1);
        target->phone[PHONE_LEN - 1] = '\0';
    }
    if (strlen(newDesc) > 0)
    {
        strncpy(target->desc, newDesc, DESC_LEN - 1);
        target->desc[DESC_LEN - 1] = '\0';
    }
}

void freeAllUser()
{
    User* p = userHead;
    while (p != NULL)
    {
        User* temp = p;
        p = p->next;
        free(temp);
    }
    userHead = NULL;
    loginUser = NULL;
}

// ==================== 文件读写 ====================
void loadUserData()
{
    FILE* fp = fopen("user.txt", "r");
    if (fp == NULL)
    {
        fp = fopen("user.txt", "w");
        fclose(fp);
        return;
    }
    // 全部使用标准宏 USER_NAME_LEN，无 NAME_LEN
    char uid[UID_LEN], name[USER_NAME_LEN], pwd[PWD_LEN], phone[PHONE_LEN], desc[DESC_LEN];
    while (fscanf(fp, "%19[^,],%29[^,],%19[^,],%14[^,],%99[^\n]\n",
        uid, name, pwd, phone, desc) != EOF)
    {
        User* node = createUserNode(uid, name, pwd, phone, desc);
        if (node != NULL)
            addUser(node);
    }
    fclose(fp);
}

void saveUserData()
{
    FILE* fp = fopen("user.txt", "w");
    if (fp == NULL)
    {
        printf("用户文件打开失败！\n");
        return;
    }
    User* p = userHead;
    while (p != NULL)
    {
        fprintf(fp, "%s,%s,%s,%s,%s\n",
            p->uid, p->username, p->password, p->phone, p->desc);
        p = p->next;
    }
    fclose(fp);
}

// ==================== 业务功能（仅保留一份，无重复定义） ====================
int userRegister()
{
    char uid[UID_LEN], name[USER_NAME_LEN], pwd[PWD_LEN], phone[PHONE_LEN], desc[DESC_LEN];
    printf("====用户注册====\n");
    printf("请输入账号(学号)：");
    scanf("%19s", uid);
    if (findUserByUid(uid) != NULL)
    {
        printf("该账号已注册，注册失败！\n");
        return 0;
    }
    printf("请输入昵称：");
    scanf("%29s", name);
    printf("请输入密码：");
    scanf("%19s", pwd);
    printf("请输入手机号：");
    scanf("%14s", phone);
    getchar();
    printf("请输入个人简介：");
    fgets(desc, DESC_LEN, stdin);
    desc[strcspn(desc, "\n")] = '\0';

    User* newUser = createUserNode(uid, name, pwd, phone, desc);
    if (newUser == NULL)
    {
        printf("注册失败：内存分配错误！\n");
        return 0;
    }
    addUser(newUser);
    saveUserData();
    printf("注册成功！\n");
    return 1;
}

int userLogin()
{
    char uid[UID_LEN], pwd[PWD_LEN];
    printf("====用户登录====\n");
    printf("账号：");
    scanf("%19s", uid);
    printf("密码：");
    scanf("%19s", pwd);

    User* u = findUserByUid(uid);
    if (u == NULL)
    {
        printf("账号不存在！\n");
        return 0;
    }
    if (strcmp(u->password, pwd) != 0)
    {
        printf("密码错误！\n");
        return 0;
    }
    loginUser = u;
    printf("登录成功！欢迎 %s\n", loginUser->username);
    return 1;
}

void modifyInfo()
{
    if (loginUser == NULL)
    {
        printf("请先登录账号！\n");
        return;
    }
    // 统一使用 USER_NAME_LEN，彻底消除 NAME_LEN 未定义报错
    char newName[USER_NAME_LEN] = "", newPhone[PHONE_LEN] = "", newDesc[DESC_LEN] = "";
    printf("====修改个人信息====\n");
    printf("当前昵称：%s，请输入新昵称（回车不修改）：", loginUser->username);
    scanf("%29s", newName);
    printf("当前手机号：%s，请输入新手机号（回车不修改）：", loginUser->phone);
    scanf("%14s", newPhone);
    getchar();
    printf("当前简介：%s，请输入新简介（回车不修改）：", loginUser->desc);
    fgets(newDesc, DESC_LEN, stdin);
    newDesc[strcspn(newDesc, "\n")] = '\0';

    updateUser(loginUser, newName, newPhone, newDesc);
    saveUserData();
    printf("信息修改成功！\n");
}
