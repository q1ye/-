#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "goods.h"
#include "file_io.h"

Goods* goodsHead = NULL;

// 创建单个商品节点
Goods* createGoodsNode(int id, char* uid, char* name, char* cate, float price, char* desc, char* time) {
    Goods* node = (Goods*)malloc(sizeof(Goods));
    node->id = id;
    strcpy(node->uid, uid);
    strcpy(node->name, name);
    strcpy(node->category, cate);
    node->price = price;
    strcpy(node->desc, desc);
    strcpy(node->time, time);
    node->status = GOODS_ONSALE;
    node->next = NULL;
    return node;
}

// 链表尾部新增商品
void addGoods(Goods* newNode) {
    if (goodsHead == NULL) {
        goodsHead = newNode;
        return;
    }
    Goods* p = goodsHead;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
}

// 根据商品ID查找商品
Goods* findGoodsById(int gid) {
    Goods* p = goodsHead;
    while (p != NULL) {
        if (p->id == gid) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 释放全部商品链表内存
void freeAllGoods() {
    Goods* p = goodsHead;
    while (p != NULL) {
        Goods* temp = p;
        p = p->next;
        free(temp);
    }
    goodsHead = NULL;
}

// 获取当前系统时间
void getNowTime(char* buf) {
    time_t t = time(NULL);
    strftime(buf, 25, "%Y-%m-%d %H:%M:%S", localtime(&t));
}

// 发布商品
void publishGoods(char* loginUid) {
    char name[50], cate[30], desc[200], t[25];
    float price;
    // 自增ID：遍历链表拿到最大id+1
    int newId = 1;
    Goods* p = goodsHead;
    while (p != NULL) {
        if (p->id >= newId) newId = p->id + 1;
        p = p->next;
    }

    printf("=====发布二手商品=====\n");
    printf("商品名称：");
    scanf("%s", name);
    getchar();
    printf("商品分类：");
    scanf("%s", cate);
    getchar();
    printf("商品价格：");
    scanf("%f", &price);
    getchar();
    printf("商品描述：");
    fgets(desc, 200, stdin);
    desc[strcspn(desc, "\n")] = '\0';

    getNowTime(t);
    Goods* newG = createGoodsNode(newId, loginUid, name, cate, price, desc, t);
    addGoods(newG);
    saveGoodsToFile(); // 写入文件持久化
    printf("商品发布成功！ID：%d\n", newId);
}

// 展示所有在售商品
void showAllOnSaleGoods() {
    Goods* p = goodsHead;
    if (goodsHead == NULL) {
        printf("暂无商品\n");
        return;
    }
    printf("=====在售商品列表=====\n");
    printf("%-5s %-10s %-8s %-6s %s\n", "ID", "名称", "分类", "价格", "发布人");
    int has = 0;
    while (p != NULL) {
        if (p->status == GOODS_ONSALE) {
            has = 1;
            printf("%-5d %-10s %-8s %.2f    %s\n", p->id, p->name, p->category, p->price, p->uid);
        }
        p = p->next;
    }
    if (!has) printf("当前无在售商品\n");
}

// 编辑商品（仅发布者可改）
void editGoods(char* loginUid) {
    int gid;
    printf("输入要修改的商品ID：");
    scanf("%d", &gid);
    Goods* g = findGoodsById(gid);
    if (g == NULL) {
        printf("商品不存在\n");
        return;
    }
    // 权限校验
    if (strcmp(g->uid, loginUid) != 0) {
        printf("无权修改他人商品\n");
        return;
    }
    printf("新商品名：");
    scanf("%s", g->name);
    getchar();
    printf("新分类：");
    scanf("%s", g->category);
    getchar();
    printf("新价格：");
    scanf("%f", &g->price);
    getchar();
    printf("新描述：");
    fgets(g->desc, 200, stdin);
    g->desc[strcspn(g->desc, "\n")] = '\0';
    saveGoodsToFile();
    printf("修改完成\n");
}

// 下架商品
void offGoods(char* loginUid) {
    int gid;
    printf("输入下架商品ID：");
    scanf("%d", &gid);
    Goods* g = findGoodsById(gid);
    if (g == NULL) {
        printf("商品不存在\n");
        return;
    }
    if (strcmp(g->uid, loginUid) != 0) {
        printf("无权操作\n");
        return;
    }
    g->status = GOODS_OFF;
    saveGoodsToFile();
    printf("商品已下架\n");
}
