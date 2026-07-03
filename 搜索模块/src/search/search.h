#ifndef SEARCH_H
#define SEARCH_H
#include "../goods/goods.h"

typedef struct SearchCondition {
    char keyword[50];
    char category[20];
    float min_price;
    float max_price;
} SearchCond;

void init_search_cond(SearchCond *cond);
void get_user_search_input(SearchCond *cond);
int goods_match_condition(Goods *g, SearchCond *cond);
void search_goods(GoodsList goods_head, SearchCond cond);
void sort_search_result(GoodsList res_list, int sort_type);

#endif