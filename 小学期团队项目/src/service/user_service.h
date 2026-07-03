#ifndef GOODS_SERVICE_H
#define GOODS_SERVICE_H

#include <time.h>
#include "../data/goods.h"

// 下面你原本所有函数声明不动
void servicePublishGoods(User* loginUser, GoodsList goodsHead);
int serviceEditGoods(User* loginUser, int gid, char* newName, char* newCate, float newPrice, char* newDesc);
int serviceOffGoods(User* loginUser, int gid);
int serviceDelGoods(User* loginUser, int gid);
void serviceShowOnSale(GoodsList goodsHead);

#endif