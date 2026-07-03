#include "goods.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GoodsList create_goods_list() {
    GoodsList head = (GoodsList)malloc(sizeof(Goods));
    if (!head) {
        perror("malloc head fail");
        exit(1);
    }
    head->next = NULL;
    return head;
}

void add_goods(GoodsList head, Goods g) {
    Goods *newNode = (Goods*)malloc(sizeof(Goods));
    if (!newNode) {
        perror("malloc goods node fail");
        return;
    }
    *newNode = g;
    newNode->next = NULL;

    Goods *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
}

int del_goods_by_id(GoodsList head, int gid) {
    Goods *p = head, *q;
    while (p->next != NULL) {
        q = p->next;
        if (q->id == gid) {
            p->next = q->next;
            free(q);
            return 1;
        }
        p = p->next;
    }
    return 0;
}

int modify_goods_by_id(GoodsList head, int gid, Goods newInfo) {
    Goods *p = head->next;
    while (p != NULL) {
        if (p->id == gid) {
            strcpy(p->name, newInfo.name);
            strcpy(p->category, newInfo.category);
            p->price = newInfo.price;
            strcpy(p->desc, newInfo.desc);
            p->status = newInfo.status;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

Goods* find_goods_by_id(GoodsList head, int gid) {
    Goods *p = head->next;
    while (p != NULL) {
        if (p->id == gid) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void free_goods_list(GoodsList head) {
    Goods *p = head, *q;
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
}
