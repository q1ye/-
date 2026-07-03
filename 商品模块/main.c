#include <stdio.h>
#include <string.h>
#include "goods.h"
#include "file_io.h"

int main() {
    // 程序启动第一步：读取goods.txt加载商品数据
    loadGoodsFromFile();
    char loginUser[20] = "stu001"; // 模拟已登录用户，对接用户模块可替换
    int op;
    while (1) {
        printf("\n=====商品模块菜单=====\n");
        printf("1.发布商品 2.浏览在售商品 3.编辑商品 4.下架商品 0.退出\n");
        printf("请输入操作：");
        scanf("%d", &op);
        switch(op) {
            case 1: publishGoods(loginUser); break;
            case 2: showAllOnSaleGoods(); break;
            case 3: editGoods(loginUser); break;
            case 4: offGoods(loginUser); break;
            case 0: freeAllGoods(); return 0;
            default: printf("输入错误\n");
        }
    }
    return 0;
}
