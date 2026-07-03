#ifndef GOODS_H
#define GOODS_H
#include "user.h" // 引入统一宏，不再重复TIME_LEN

#define GOODS_ID_LEN 20
#define GOODS_NAME_LEN 50
#define GOODS_CAT_LEN 30
#define GOODS_DESC_LEN 200
#define GOODS_ONSALE 0
#define GOODS_OFF 1
#define GOODS_SOLD 2

typedef struct Goods{
    int id;
    char gid[GOODS_ID_LEN];
    char uid[UID_LEN];
    char name[GOODS_NAME_LEN];
    char category[GOODS_CAT_LEN];
    float price;
    char desc[GOODS_DESC_LEN];
    int status;
    char time[TIME_LEN];
    struct Goods* next;
}Goods,*GoodsList;

extern Goods* goodsHead;

Goods* createGoodsNode(int id,char* uid,char* name,char* cate,float price,char* desc,char* t);
void addGoods(Goods* node);
Goods* findGoodsById(int id);
Goods* SearchGoodsById(GoodsList L,char* gid);
void freeAllGoods();
void publishGoods(char* loginUid);
void showAllOnSaleGoods();
int editGoodsById(char* loginUid,int gid,Goods newInfo);
int offGoodsById(char* loginUid,int gid);
int delGoodsById(char* loginUid,int gid);
int DelGoods(GoodsList* L,char* gid);
void saveGoodsToFile();
void LoadGoodsFromFile(GoodsList* L,const char* path);
void InitGoodsList(GoodsList* L);
#endif