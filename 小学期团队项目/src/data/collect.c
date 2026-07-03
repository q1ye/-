#include "collect.h"

void InitCollectList(CollectList *L) {
    *L = (Collect*)malloc(sizeof(Collect));
    (*L)->next = NULL;
}

int AddCollect(CollectList *L, char *uid, char *gid) {
    Collect *newNode = (Collect*)malloc(sizeof(Collect));
    strcpy(newNode->uid, uid);
    strcpy(newNode->gid, gid);
    newNode->next = (*L)->next;
    (*L)->next = newNode;
    return 1;
}

int DelCollect(CollectList *L, char *uid, char *gid) {
    Collect *pre = *L, *p = pre->next;
    while(p) {
        if(strcmp(p->uid, uid) == 0 && strcmp(p->gid, gid) == 0) {
            pre->next = p->next;
            free(p);
            return 1;
        }
        pre = p;
        p = p->next;
    }
    return 0;
}

Collect* SearchUserCollect(CollectList L, char *uid) {
    return L->next; // 上层遍历过滤uid即可
}

int IsCollected(CollectList L, char *uid, char *gid) {
    Collect *p = L->next;
    while(p) {
        if(strcmp(p->uid, uid) == 0 && strcmp(p->gid, gid) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

void SaveCollectToFile(CollectList L, const char *filePath) {
    FILE *fp = fopen(filePath, "wb");
    if (!fp) return;
    Collect *p = L->next;
    while (p) {
        fwrite(p, sizeof(Collect), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void LoadCollectFromFile(CollectList *L, const char *filePath) {
    FILE *fp = fopen(filePath, "rb");
    if (!fp) return;
    Collect temp;
    while (fread(&temp, sizeof(Collect), 1, fp) == 1) {
        AddCollect(L, temp.uid, temp.gid);
    }
    fclose(fp);
}

void FreeCollectList(CollectList *L) {
    Collect *p = (*L)->next, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}
