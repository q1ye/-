#ifndef GOODS_H
#define GOODS_H

// 商品状态常量
#define GOODS_ONSALE 0    // 在售
#define GOODS_OFF 1       // 下架
#define GOODS_SOLD 2      // 已售出

// 商品结构体
typedef struct Goods {
    int id;               // 商品唯一ID
    char uid[20];         // 发布用户ID
    char name[50];        // 商品名
    char category[30];    // 分类
    float price;          // 价格
    char desc[200];       // 描述
    int status;           // 状态
    char time[25];        // 发布时间
    struct Goods* next;   // 链表指针
} Goods;

// 全局商品链表头
extern Goods* goodsHead;

// 函数声明
// 1. 链表操作
Goods* createGoodsNode(int id, char* uid, char* name, char* cate, float price, char* desc, char* time);
void addGoods(Goods* newNode);
Goods* findGoodsById(int gid);
void freeAllGoods();

// 2. 业务功能
void publishGoods(char* loginUid);    // 发布商品
void showAllOnSaleGoods();            // 浏览在售商品
void editGoods(char* loginUid);       // 编辑商品
void offGoods(char* loginUid);        // 下架商品

#endif