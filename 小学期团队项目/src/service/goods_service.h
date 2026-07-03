#ifndef GOODS_SERVICE_H
#define GOODS_SERVICE_H
#include "../data/goods.h"

// 发布商品
void servicePublishGoods(User* loginUser, GoodsList goodsHead);
// 编辑商品
int serviceEditGoods(User* loginUser, int gid, char* newName, char* newCate, float newPrice, char* newDesc);
// 下架商品
int serviceOffGoods(User* loginUser, int gid);
// 删除商品
int serviceDelGoods(User* loginUser, int gid);
// 展示所有在售商品
void serviceShowOnSale(GoodsList goodsHead);

#endif