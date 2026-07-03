#include "goods_service.h"
#include <string.h>

void servicePublishGoods(User* loginUser, GoodsList goodsHead)
{
    if (!loginUser) return;
    char name[GOODS_NAME_LEN], cate[GOODS_CAT_LEN], desc[GOODS_DESC_LEN], t[TIME_LEN];
    float price;
    int newId = 1;
    Goods* p = goodsHead;
    while (p)
    {
        if (p->id >= newId) newId = p->id + 1;
        p = p->next;
    }
    printf("商品名称：");
    scanf("%s", name);
    printf("分类：");
    scanf("%s", cate);
    printf("价格：");
    scanf("%f", &price);
    getchar();
    printf("描述：");
    fgets(desc, GOODS_DESC_LEN, stdin);
    desc[strcspn(desc, "\n")] = 0;

    strcpy(t, "2026-07-04 12:00:00");

    Goods* newG = createGoodsNode(newId, loginUser->uid, name, cate, price, desc, t);
    addGoods(newG);
    saveGoodsToFile();
    printf("发布成功，商品ID：%d\n", newId);
}

int serviceEditGoods(User* loginUser, int gid, char* newName, char* newCate, float newPrice, char* newDesc)
{
    Goods* g = findGoodsById(gid);
    if (!g) return 0;
    if (strcmp(g->uid, loginUser->uid) != 0) return 0;
    strcpy(g->name, newName);
    strcpy(g->category, newCate);
    g->price = newPrice;
    strcpy(g->desc, newDesc);
    saveGoodsToFile();
    return 1;
}

int serviceOffGoods(User* loginUser, int gid)
{
    Goods* g = findGoodsById(gid);
    if (!g) return 0;
    if (strcmp(g->uid, loginUser->uid) != 0) return 0;
    g->status = GOODS_OFF;
    saveGoodsToFile();
    return 1;
}

int serviceDelGoods(User* loginUser, int gid)
{
    extern Goods* goodsHead;
    Goods* p = goodsHead, *pre = NULL;
    while (p && p->id != gid)
    {
        pre = p;
        p = p->next;
    }
    if (!p) return 0;
    if (strcmp(p->uid, loginUser->uid) != 0) return 0;
    if (pre == NULL)
        goodsHead = p->next;
    else
        pre->next = p->next;
    free(p);
    saveGoodsToFile();
    return 1;
}

void serviceShowOnSale(GoodsList goodsHead)
{
    Goods* p = goodsHead;
    int flag = 0;
    printf("====在售商品列表====\n");
    while (p)
    {
        if (p->status == GOODS_ONSALE)
        {
            flag = 1;
            printf("ID:%d 名称:%s 分类:%s 价格:%.2f 发布人:%s\n",
                   p->id, p->name, p->category, p->price, p->uid);
        }
        p = p->next;
    }
    if (!flag) printf("暂无在售商品\n");
}