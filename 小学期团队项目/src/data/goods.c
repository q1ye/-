#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "goods.h"
#include "file_io.h"

// 全局商品链表头
Goods* goodsHead = NULL;

// ===================== 链表基础操作 =====================
// 创建商品节点（核心逻辑保留，补充gid默认值）
Goods* createGoodsNode(int id, char* uid, char* name, char* cate, float price, char* desc, char* time) {
    Goods* node = (Goods*)malloc(sizeof(Goods));
    if (!node) {
        perror("malloc goods node fail");
        return NULL;
    }
    // 初始化节点字段
    node->id = id;
    snprintf(node->gid, GOODS_ID_LEN, "%d", id); // int ID转字符串gid，保证兼容
    strncpy(node->uid, uid, UID_LEN - 1);
    node->uid[UID_LEN - 1] = '\0';
    strncpy(node->name, name, GOODS_NAME_LEN - 1);
    node->name[GOODS_NAME_LEN - 1] = '\0';
    strncpy(node->category, cate, GOODS_CAT_LEN - 1);
    node->category[GOODS_CAT_LEN - 1] = '\0';
    node->price = price;
    strncpy(node->desc, desc, GOODS_DESC_LEN - 1);
    node->desc[GOODS_DESC_LEN - 1] = '\0';
    strncpy(node->time, time, TIME_LEN - 1);
    node->time[TIME_LEN - 1] = '\0';
    node->status = GOODS_ONSALE; // 默认在售
    node->next = NULL;
    return node;
}

// 尾插法添加商品节点
void addGoods(Goods* newNode) {
    if (!newNode) return;
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

// 按int ID查找商品
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

// 按字符串ID查找商品（兼容原逻辑）
Goods* SearchGoodsById(GoodsList L, char *gid) {
    Goods *p = L->next;
    while(p) {
        if(strcmp(p->gid, gid) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

// 释放所有商品链表内存
void freeAllGoods() {
    Goods* p = goodsHead;
    while (p != NULL) {
        Goods* temp = p;
        p = p->next;
        free(temp);
    }
    goodsHead = NULL;
}

// 初始化商品链表（兼容原GoodsList逻辑）
void InitGoodsList(GoodsList *L) {
    *L = (Goods*)malloc(sizeof(Goods));
    (*L)->next = NULL;
}

// ===================== 工具函数 =====================
// 获取当前系统时间
static void getNowTime(char* buf) {
    if (!buf) return;
    time_t t = time(NULL);
    strftime(buf, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&t));
}

// ===================== 业务功能操作 =====================
// 发布商品（自动生成ID、记录发布时间）
void publishGoods(char* loginUid) {
    if (!loginUid) return;

    char name[GOODS_NAME_LEN], cate[GOODS_CAT_LEN], desc[GOODS_DESC_LEN], t[TIME_LEN];
    float price;

    // 自动生成商品ID（最大ID+1）
    int newId = 1;
    Goods* p = goodsHead;
    while (p != NULL) {
        if (p->id >= newId) newId = p->id + 1;
        p = p->next;
    }

    // 输入商品信息
    printf("=====发布商品=====\n");
    printf("商品名称：");
    scanf("%s", name);
    getchar(); // 吸收换行符
    printf("商品分类：");
    scanf("%s", cate);
    getchar();
    printf("商品价格：");
    scanf("%f", &price);
    getchar();
    printf("商品描述：");
    fgets(desc, GOODS_DESC_LEN, stdin);
    desc[strcspn(desc, "\n")] = '\0'; // 去除换行符

    // 生成发布时间
    getNowTime(t);
    // 创建节点并添加到链表
    Goods* newG = createGoodsNode(newId, loginUid, name, cate, price, desc, t);
    if (newG) {
        addGoods(newG);
        saveGoodsToFile(); // 持久化到文件
        printf("商品发布成功！ID：%d\n", newId);
    } else {
        printf("商品发布失败，内存分配失败\n");
    }
}

// 浏览所有在售商品
void showAllOnSaleGoods() {
    Goods* p = goodsHead;
    if (goodsHead == NULL) {
        printf("暂无商品\n");
        return;
    }
    printf("=====在售商品列表=====\n");
    printf("%-5s %-10s %-8s %-6s %s\n", "ID", "名称", "分类", "价格", "发布者");
    int hasOnSale = 0;
    while (p != NULL) {
        if (p->status == GOODS_ONSALE) {
            hasOnSale = 1;
            printf("%-5d %-10s %-8s %.2f    %s\n",
                   p->id, p->name, p->category, p->price, p->uid);
        }
        p = p->next;
    }
    if (!hasOnSale) printf("当前无在售商品\n");
}

// 编辑商品（带权限校验）
int editGoodsById(char* loginUid, int gid, Goods newInfo) {
    if (!loginUid) return 0;
    Goods* g = findGoodsById(gid);
    if (g == NULL) {
        printf("商品不存在\n");
        return 0;
    }
    // 权限校验：仅发布者可编辑
    if (strcmp(g->uid, loginUid) != 0) {
        printf("无权编辑该商品\n");
        return 0;
    }
    // 更新商品信息
    strncpy(g->name, newInfo.name, GOODS_NAME_LEN - 1);
    g->name[GOODS_NAME_LEN - 1] = '\0';
    strncpy(g->category, newInfo.category, GOODS_CAT_LEN - 1);
    g->category[GOODS_CAT_LEN - 1] = '\0';
    g->price = newInfo.price;
    strncpy(g->desc, newInfo.desc, GOODS_DESC_LEN - 1);
    g->desc[GOODS_DESC_LEN - 1] = '\0';
    g->status = newInfo.status;

    saveGoodsToFile(); // 持久化
    printf("商品编辑成功\n");
    return 1;
}

// 下架商品（带权限校验）
int offGoodsById(char* loginUid, int gid) {
    if (!loginUid) return 0;
    Goods* g = findGoodsById(gid);
    if (g == NULL) {
        printf("商品不存在\n");
        return 0;
    }
    // 权限校验：仅发布者可下架
    if (strcmp(g->uid, loginUid) != 0) {
        printf("无权下架该商品\n");
        return 0;
    }
    g->status = GOODS_OFF;
    saveGoodsToFile(); // 持久化
    printf("商品已下架\n");
    return 1;
}

// 删除商品（带权限校验，int ID版）
int delGoodsById(char* loginUid, int gid) {
    if (!loginUid || goodsHead == NULL) return 0;

    Goods *p = goodsHead, *q = NULL;
    // 处理头节点是目标商品的情况
    if (p->id == gid) {
        if (strcmp(p->uid, loginUid) != 0) {
            printf("无权删除该商品\n");
            return 0;
        }
        goodsHead = p->next;
        free(p);
        saveGoodsToFile();
        printf("商品删除成功\n");
        return 1;
    }
    // 处理非头节点的情况
    while (p != NULL && p->id != gid) {
        q = p;
        p = p->next;
    }
    if (p == NULL) {
        printf("商品不存在\n");
        return 0;
    }
    // 权限校验
    if (strcmp(p->uid, loginUid) != 0) {
        printf("无权删除该商品\n");
        return 0;
    }
    q->next = p->next;
    free(p);
    saveGoodsToFile();
    printf("商品删除成功\n");
    return 1;
}

// 按字符串ID删除商品（兼容原逻辑）
int DelGoods(GoodsList *L, char *gid) {
    Goods *pre = *L, *p = pre->next;
    while(p) {
        if(strcmp(p->gid, gid) == 0) {
            pre->next = p->next;
            free(p);
            saveGoodsToFile();
            return 1;
        }
        pre = p;
        p = p->next;
    }
    return 0;
}

// ===================== 文件IO操作 =====================
// 保存商品链表到文件（核心逻辑，需结合file_io.h实现，此处保留接口）
void saveGoodsToFile() {
    // 实际实现需参考file_io.h的定义，示例逻辑：
    FILE *fp = fopen("goods.dat", "wb");
    if(!fp) {
        perror("save goods to file fail");
        return;
    }
    Goods *p = goodsHead;
    while(p) {
        fwrite(p, sizeof(Goods), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

// 从文件加载商品链表（兼容原逻辑）
void LoadGoodsFromFile(GoodsList *L, const char *path) {
    FILE *fp = fopen(path, "rb");
    if(!fp) {
        perror("load goods from file fail");
        return;
    }
    Goods temp;
    while(fread(&temp, sizeof(Goods), 1, fp) == 1) {
        Goods *newNode = (Goods*)malloc(sizeof(Goods));
        *newNode = temp;
        newNode->next = (*L)->next;
        (*L)->next = newNode;
    }
    fclose(fp);
}
