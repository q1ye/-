#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 字符长度宏定义，统一规范
#define UID_LEN 20
#define NAME_LEN 30
#define PWD_LEN 20
#define PHONE_LEN 15
#define DESC_LEN 100

// 用户结构体
typedef struct User {
    char uid[UID_LEN];       // 账号/学号，唯一标识
    char username[NAME_LEN]; // 昵称
    char password[PWD_LEN];  // 密码
    char phone[PHONE_LEN];   // 手机号
    char desc[DESC_LEN];     // 个人简介
    struct User* next;
} User;

// 全局链表头：存储全部用户
extern User* userHead;
// 当前登录用户指针
extern User* loginUser;

// 底层链表操作接口
User* createUserNode(char* uid, char* name, char* pwd, char* phone, char* desc);
void addUser(User* newNode);
User* findUserByUid(char* uid);
void updateUser(User* target, char* newName, char* newPhone, char* newDesc);
void freeAllUser();

// 文件持久化接口
void loadUserData();  // 启动时读取user.txt
void saveUserData();  // 修改后保存到user.txt

// 业务功能接口
int userRegister();   // 注册，返回1成功0失败
int userLogin();      // 登录，返回1成功0失败
void modifyInfo();    // 修改个人信息

#endif