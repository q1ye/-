#ifndef GOODS_H
#define GOODS_H
#include "user.h"

#define GOODS_ID_LEN 20
#define GOODS_NAME_LEN 50
#define GOODS_DESC_LEN 200
#define GOODS_CATE_LEN 30

typedef struct Goods {
    char gid[GOODS_ID_LEN];
    char uid[USER_ID_LEN];    // 发布者ID
    char name[GOODS_NAME_LEN];
    char category[GOODS_CATE_LEN];
    double price;
    char desc[GOODS_DESC_LEN];
    int status; // 0下架 1上架
    struct Goods *next;
} Goods, *GoodsList;

void InitGoodsList(GoodsList *L);
Goods* SearchGoodsById(GoodsList L, char *gid);
int AddGoods(GoodsList *L, Goods g);
int DelGoods(GoodsList *L, char *gid);
void SaveGoodsToFile(GoodsList L, const char *path);
void LoadGoodsFromFile(GoodsList *L, const char *path);
void FreeGoodsList(GoodsList *L);
#endif