#ifndef SEARCH_H
#define SEARCH_H
#include "../data/goods.h"

// 按名称模糊搜索
void searchGoodsByName(GoodsList head, char* key);
// 按价格区间搜索
void searchGoodsByPrice(GoodsList head, float min, float max);
// 按分类搜索
void searchGoodsByCate(GoodsList head, char* cate);

#endif