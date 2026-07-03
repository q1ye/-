#include "user.h"

void InitUserList(UserList *L) {
    *L = (User*)malloc(sizeof(User));
    (*L)->next = NULL;
}

User* SearchUserById(UserList L, char *uid) {
    User *p = L->next;
    while(p) {
        if(strcmp(p->uid, uid) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

int AddUser(UserList *L, User u) {
    User *newNode = (User*)malloc(sizeof(User));
    *newNode = u;
    newNode->next = (*L)->next;
    (*L)->next = newNode;
    return 1;
}

void SaveUserToFile(UserList L, const char *path) {
    FILE *fp = fopen(path, "wb");
    if(!fp) return;
    User *p = L->next;
    while(p) {
        fwrite(p, sizeof(User), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void LoadUserFromFile(UserList *L, const char *path) {
    FILE *fp = fopen(path, "rb");
    if(!fp) return;
    User temp;
    while(fread(&temp, sizeof(User), 1, fp) == 1) {
        AddUser(L, temp);
    }
    fclose(fp);
}

void FreeUserList(UserList *L) {
    User *p = (*L)->next, *q;
    while(p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}
