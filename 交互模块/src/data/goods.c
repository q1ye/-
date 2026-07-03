#include "goods.h"

void InitGoodsList(GoodsList *L) {
    *L = (Goods*)malloc(sizeof(Goods));
    (*L)->next = NULL;
}

Goods* SearchGoodsById(GoodsList L, char *gid) {
    Goods *p = L->next;
    while(p) {
        if(strcmp(p->gid, gid) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

int AddGoods(GoodsList *L, Goods g) {
    Goods *newNode = (Goods*)malloc(sizeof(Goods));
    *newNode = g;
    newNode->next = (*L)->next;
    (*L)->next = newNode;
    return 1;
}

int DelGoods(GoodsList *L, char *gid) {
    Goods *pre = *L, *p = pre->next;
    while(p) {
        if(strcmp(p->gid, gid) == 0) {
            pre->next = p->next;
            free(p);
            return 1;
        }
        pre = p;
        p = p->next;
    }
    return 0;
}

void SaveGoodsToFile(GoodsList L, const char *path) {
    FILE *fp = fopen(path, "wb");
    if(!fp) return;
    Goods *p = L->next;
    while(p) {
        fwrite(p, sizeof(Goods), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void LoadGoodsFromFile(GoodsList *L, const char *path) {
    FILE *fp = fopen(path, "rb");
    if(!fp) return;
    Goods temp;
    while(fread(&temp, sizeof(Goods), 1, fp) == 1) {
        AddGoods(L, temp);
    }
    fclose(fp);
}

void FreeGoodsList(GoodsList *L) {
    Goods *p = (*L)->next, *q;
    while(p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}
