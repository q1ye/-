#include "user.h"

User* userHead = NULL;
User* loginUser = NULL;
// 创建单个用户节点
User* createUserNode(char* uid, char* name, char* pwd, char* phone, char* desc) {
    User* newNode = (User*)malloc(sizeof(User));
    strcpy(newNode->uid, uid);
    strcpy(newNode->username, name);
    strcpy(newNode->password, pwd);
    strcpy(newNode->phone, phone);
    strcpy(newNode->desc, desc);
    newNode->next = NULL;
    return newNode;
}

// 尾部插入用户节点
void addUser(User* newNode) {
    if (userHead == NULL) {
        userHead = newNode;
        return;
    }
    User* p = userHead;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
}

// 根据账号查找用户
User* findUserByUid(char* uid) {
    User* p = userHead;
    while (p != NULL) {
        if (strcmp(p->uid, uid) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 更新用户信息
void updateUser(User* target, char* newName, char* newPhone, char* newDesc) {
    // 输入回车不修改，保留原值
    if (strlen(newName) > 0) strcpy(target->username, newName);
    if (strlen(newPhone) > 0) strcpy(target->phone, newPhone);
    if (strlen(newDesc) > 0) strcpy(target->desc, newDesc);
}

// 释放整个用户链表内存
void freeAllUser() {
    User* p = userHead;
    while (p != NULL) {
        User* temp = p;
        p = p->next;
        free(temp);
    }
    userHead = NULL;
}
// 程序启动读取user.txt
void loadUserData() {
    FILE* fp = fopen("user.txt", "r");
    if (fp == NULL) {
        // 文件不存在，自动创建空文件
        fp = fopen("user.txt", "w");
        fclose(fp);
        return;
    }
    char uid[UID_LEN], name[NAME_LEN], pwd[PWD_LEN], phone[PHONE_LEN], desc[DESC_LEN];
    // 循环读取每行数据
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", uid, name, pwd, phone, desc) != EOF) {
        User* node = createUserNode(uid, name, pwd, phone, desc);
        addUser(node);
    }
    fclose(fp);
}

// 保存所有用户到user.txt
void saveUserData() {
    FILE* fp = fopen("user.txt", "w");
    if (fp == NULL) {
        printf("用户文件打开失败！\n");
        return;
    }
    User* p = userHead;
    while (p != NULL) {
        fprintf(fp, "%s,%s,%s,%s,%s\n", p->uid, p->username, p->password, p->phone, p->desc);
        p = p->next;
    }
    fclose(fp);
}
int userRegister() {
    char uid[UID_LEN], name[NAME_LEN], pwd[PWD_LEN], phone[PHONE_LEN], desc[DESC_LEN];
    printf("====用户注册====\n");
    printf("请输入账号(学号)：");
    scanf("%s", uid);

    // 校验账号是否重复
    if (findUserByUid(uid) != NULL) {
        printf("该账号已注册，注册失败！\n");
        return 0;
    }

    printf("请输入昵称：");
    scanf("%s", name);
    printf("请输入密码：");
    scanf("%s", pwd);
    printf("请输入手机号：");
    scanf("%s", phone);
    getchar(); // 吸收换行
    printf("个人简介：");
    gets(desc);

    // 创建节点存入链表
    User* newUser = createUserNode(uid, name, pwd, phone, desc);
    addUser(newUser);
    saveUserData(); // 写入文件持久化
    printf("注册成功！\n");
    return 1;
}
int userLogin() {
    char uid[UID_LEN], pwd[PWD_LEN];
    printf("====用户登录====\n");
    printf("账号：");
    scanf("%s", uid);
    printf("密码：");
    scanf("%s", pwd);

    User* u = findUserByUid(uid);
    if (u == NULL) {
        printf("账号不存在！\n");
        return 0;
    }
    if (strcmp(u->password, pwd) != 0) {
        printf("密码错误！\n");
        return 0;
    }
    // 登录成功，赋值全局登录用户
    loginUser = u;
    printf("登录成功，欢迎%s！\n", loginUser->username);
    return 1;
}
void modifyInfo() {
    // 判断是否登录
    if (loginUser == NULL) {
        printf("请先登录账号！\n");
        return;
    }
    char newName[NAME_LEN] = "", newPhone[PHONE_LEN] = "", newDesc[DESC_LEN] = "";
    printf("====修改个人信息====\n");
    printf("当前昵称：%s，输入新昵称(回车不变)：", loginUser->username);
    scanf("%s", newName);
    printf("当前手机号：%s，输入新手机号(回车不变)：", loginUser->phone);
    scanf("%s", newPhone);
    getchar();
    printf("当前简介：%s，输入新简介(回车不变)：", loginUser->desc);
    gets(newDesc);

    updateUser(loginUser, newName, newPhone, newDesc);
    saveUserData();
    printf("信息修改完成！\n");
}
