#include "search.h"
#include <string.h>

void searchGoodsByName(GoodsList head, char* key)
{
    Goods* p = head;
    int has = 0;
    while(p)
    {
        if(strstr(p->name, key))
        {
            has = 1;
            printf("ID:%d 名称:%s 分类:%s 价格:%.2f\n",p->id,p->name,p->category,p->price);
        }
        p = p->next;
    }
    if(!has) printf("无匹配商品\n");
}

void searchGoodsByPrice(GoodsList head, float min, float max)
{
    Goods* p = head;
    int has = 0;
    while(p)
    {
        if(p->price >= min && p->price <= max)
        {
            has = 1;
            printf("ID:%d 名称:%s 价格:%.2f\n",p->id,p->name,p->price);
        }
        p = p->next;
    }
    if(!has) printf("无匹配商品\n");
}

void searchGoodsByCate(GoodsList head, char* cate)
{
    Goods* p = head;
    int has = 0;
    while(p)
    {
        if(strcmp(p->category, cate)==0)
        {
            has = 1;
            printf("ID:%d 名称:%s 分类:%s\n",p->id,p->name,p->category);
        }
        p = p->next;
    }
    if(!has) printf("无匹配商品\n");
}
