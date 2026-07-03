#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

#define FILE_NAME "goods.txt"

void loadGoodsFromFile() {
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        // 文件不存在则自动创建
        fp = fopen(FILE_NAME, "w");
        fclose(fp);
        return;
    }
    int id, status;
    float price;
    char uid[20], name[50], cate[30], desc[200], time[25];
    // 按逗号分割读取每行数据
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%f,%[^,],%d,%[^\n]",
                  &id, uid, name, cate, &price, desc, &status, time) != EOF) {
        Goods* node = createGoodsNode(id, uid, name, cate, price, desc, time);
        node->status = status;
        addGoods(node);
    }
    fclose(fp);
}

void saveGoodsToFile() {
    FILE* fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return;
    }
    Goods* p = goodsHead;
    while (p != NULL) {
        fprintf(fp, "%d,%s,%s,%s,%.2f,%s,%d,%s\n",
                p->id, p->uid, p->name, p->category, p->price, p->desc, p->status, p->time);
        p = p->next;
    }
    fclose(fp);
}
