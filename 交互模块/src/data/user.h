#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USER_NAME_LEN 20
#define USER_PWD_LEN 20
#define USER_ID_LEN 20

typedef struct User {
    char uid[USER_ID_LEN];
    char username[USER_NAME_LEN];
    char password[USER_PWD_LEN];
    struct User *next;
} User, *UserList;

void InitUserList(UserList *L);
User* SearchUserById(UserList L, char *uid);
int AddUser(UserList *L, User u);
void SaveUserToFile(UserList L, const char *path);
void LoadUserFromFile(UserList *L, const char *path);
void FreeUserList(UserList *L);
#endif