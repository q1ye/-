#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UID_LEN 20
#define USER_NAME_LEN 30
#define PWD_LEN 20
#define PHONE_LEN 15
#define DESC_LEN 100
#define TIME_LEN 25 // 全局统一时间长度，所有文件不再重复定义

typedef struct User{
    char uid[UID_LEN];
    char username[USER_NAME_LEN];
    char password[PWD_LEN];
    char phone[PHONE_LEN];
    char desc[DESC_LEN];
    struct User* next;
}User,*UserList;

extern User* loginUser;
extern UserList userHead;

User* createUserNode(char* uid,char* name,char* pwd,char* phone,char* desc);
void addUser(User* node);
User* findUserByUid(char* uid);
void updateUser(User* u,char* n,char* p,char* d);
void freeAllUser();
void loadUserData();
void saveUserData();
int userRegister();
int userLogin();
void modifyInfo();

void InitUserList(UserList* L);
User* SearchUserById(UserList L,char* uid);
int AddUser(UserList* L,User u);
void SaveUserToFile(UserList L,const char* path);
void LoadUserFromFile(UserList* L,const char* path);
void FreeUserList(UserList* L);
#endif