#ifndef GOODS_H
#define GOODS_H

#define GOODS_NAME_LEN 50
#define GOODS_CAT_LEN 20
#define GOODS_DESC_LEN 100

typedef struct Goods {
    int id;
    char name[GOODS_NAME_LEN];
    char category[GOODS_CAT_LEN];
    float price;
    char desc[GOODS_DESC_LEN];
    int uid;
    int status;
    struct Goods *next;
} Goods, *GoodsList;

GoodsList create_goods_list();
void add_goods(GoodsList head, Goods g);
int del_goods_by_id(GoodsList head, int gid);
int modify_goods_by_id(GoodsList head, int gid, Goods newInfo);
Goods* find_goods_by_id(GoodsList head, int gid);
void free_goods_list(GoodsList head);

#endif