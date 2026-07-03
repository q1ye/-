#include "search.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void init_search_cond(SearchCond *cond) {
    memset(cond->keyword, 0, sizeof(cond->keyword));
    memset(cond->category, 0, sizeof(cond->category));
    cond->min_price = -1;
    cond->max_price = -1;
}

void get_user_search_input(SearchCond *cond) {
    init_search_cond(cond);
    printf("=====商品搜索筛选面板=====\n");
    printf("1. 输入关键词（名称/描述模糊搜索，直接回车跳过）：");
    getchar();
    fgets(cond->keyword, 50, stdin);
    cond->keyword[strcspn(cond->keyword, "\n")] = '\0';

    printf("2. 输入商品分类（如书籍/数码/服饰，回车跳过）：");
    fgets(cond->category, 20, stdin);
    cond->category[strcspn(cond->category, "\n")] = '\0';

    printf("3. 设置价格区间（无下限输入-1，无上限输入-1）\n");
    printf("最低价格：");
    scanf("%f", &cond->min_price);
    printf("最高价格：");
    scanf("%f", &cond->max_price);
}

int goods_match_condition(Goods *g, SearchCond *cond) {
    if (g->status != 1) return 0;

    if (strlen(cond->keyword) > 0) {
        if (!strstr(g->name, cond->keyword) && !strstr(g->desc, cond->keyword))
            return 0;
    }

    if (strlen(cond->category) > 0) {
        if (strcmp(g->category, cond->category) != 0)
            return 0;
    }

    if (cond->min_price != -1 && g->price < cond->min_price)
        return 0;
    if (cond->max_price != -1 && g->price > cond->max_price)
        return 0;

    return 1;
}

void search_goods(GoodsList goods_head, SearchCond cond) {
    Goods *p = goods_head->next;
    int count = 0;
    printf("\n==========搜索结果==========\n");
    while (p != NULL) {
        if (goods_match_condition(p, &cond)) {
            count++;
            printf("编号：%d | 名称：%s | 分类：%s | 价格：%.2f元\n",
                   p->id, p->name, p->category, p->price);
            printf("描述：%s\n----------------------------\n", p->desc);
        }
        p = p->next;
    }
    if (count == 0) {
        printf("未找到符合筛选条件的上架商品！\n");
    } else {
        printf("本次共检索到 %d 件商品\n", count);
    }
}

void sort_search_result(GoodsList res_list, int sort_type) {
    if (res_list->next == NULL || res_list->next->next == NULL) return;
    Goods *p, *q;
    float temp_price;
    char temp_name[50], temp_cat[20], temp_desc[100];
    int temp_id, temp_uid, temp_status;
    for (p = res_list->next; p->next != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if ((sort_type == 1 && p->price > q->price) || (sort_type == 2 && p->price < q->price)) {
                temp_id = p->id; p->id = q->id; q->id = temp_id;
                temp_price = p->price; p->price = q->price; q->price = temp_price;
                strcpy(temp_name, p->name); strcpy(p->name, q->name); strcpy(q->name, temp_name);
                strcpy(temp_cat, p->category); strcpy(p->category, q->category); strcpy(q->category, temp_cat);
                strcpy(temp_desc, p->desc); strcpy(p->desc, q->desc); strcpy(q->desc, temp_desc);
                temp_uid = p->uid; p->uid = q->uid; q->uid = temp_uid;
                temp_status = p->status; p->status = q->status; q->status = temp_status;
            }
        }
    }
}
