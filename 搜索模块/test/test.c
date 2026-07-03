#include "../src/search/search.h"
#include "../src/goods/goods.h"
#include <stdio.h>

int main() {
    GoodsList head = createGoodsList();
    // 模拟测试商品数据
    Goods g1 = {1, "C语言教材", "书籍", 25.5, "全新课本", 1001, 1, NULL};
    Goods g2 = {2, "蓝牙耳机", "数码", 89, "几乎全新", 1002, 1, NULL};
    Goods g3 = {3, "旧笔记本", "数码", 350, "卡顿低价出", 1003, 0, NULL};
    addGoods(head, g1);
    addGoods(head, g2);
    addGoods(head, g3);

    SearchCond cond;
    // 测试1：关键词搜索
    initCond(&cond);
    strcpy(cond.keyword, "数码");
    searchAllGoods(head, cond);

    // 测试2：价格区间筛选
    initCond(&cond);
    cond.minPrice = 50;
    cond.maxPrice = 100;
    searchAllGoods(head, cond);
    return 0;
}
