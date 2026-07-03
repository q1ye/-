#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_io.h"

// 从文件加载商品到链表
void loadGoodsFromFile() {
    // 以只读模式打开文件
    FILE* fp = fopen(GOODS_FILE_PATH, "r");
    if (fp == NULL) {
        // 文件不存在则创建空文件，避免后续读写报错
        fp = fopen(GOODS_FILE_PATH, "w");
        if (fp != NULL) {
            fclose(fp);  // 确保文件创建后关闭
        }
        return;
    }

    // 定义读取缓冲区，覆盖两个版本的所有字段
    int id, status;
    float price;
    char uid[20], name[50], category[30], desc[200], time[25];

    // 按格式读取每行数据（兼容 id,uid,name,category,price,desc,status,time 格式）
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%f,%[^,],%d,%[^\n]",
                  &id, uid, name, category, &price, desc, &status, time) != EOF) {
        // 创建商品节点（需确保 goods.h 中实现了 createGoodsNode 函数）
        Goods* node = createGoodsNode(id, uid, name, category, price, desc, time);
        if (node != NULL) {  // 空指针检查，避免崩溃
            node->status = status;
            addGoods(node);  // 需确保 goods.h 中实现了 addGoods 函数
        }
    }

    fclose(fp);  // 确保文件句柄释放
}

// 将链表中所有商品写入文件
void saveGoodsToFile() {
    // 以写入模式打开文件（覆盖原内容）
    FILE* fp = fopen(GOODS_FILE_PATH, "w");
    if (fp == NULL) {
        perror("打开商品文件失败");  // 替换中文乱码，使用标准错误提示
        return;
    }

    // 遍历商品链表（goodsHead 需在 goods.h 中定义为链表头节点）
    Goods* p = goodsHead;
    while (p != NULL) {
        // 按格式写入每行数据，价格保留 2 位小数
        fprintf(fp, "%d,%s,%s,%s,%.2f,%s,%d,%s\n",
                p->id, p->uid, p->name, p->category, p->price, p->desc, p->status, p->time);
        p = p->next;
    }

    fclose(fp);  // 确保文件句柄释放
}
