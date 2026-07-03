#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_struct/linklist.h"
#include "goods/goods.h"
#include "search/search.h"
#include "file_io/file_io.h"

void show_main_menu() {
    printf("====================校园二手交易平台====================\n");
    printf("1. 发布商品\n");
    printf("2. 商品搜索（多条件筛选）\n");
    printf("0. 退出系统\n");
    printf("========================================================\n");
    printf("请输入操作序号：");
}

int main() {
    GoodsList goods_head = create_goods_list();
    load_goods_from_file(goods_head);

    int op;
    SearchCond cond;

    while (1) {
        show_main_menu();
        scanf("%d", &op);
        switch (op) {
            case 2:
                get_user_search_input(&cond);
                search_goods(goods_head, cond);
                break;
            case 0:
                save_goods_to_file(goods_head);
                free_goods_list(goods_head);
                printf("数据已保存，程序退出！\n");
                return 0;
            default:
                printf("输入错误，请重新选择！\n");
                break;
        }
        printf("\n按下回车继续...");
        getchar();
        getchar();
        system("cls");
    }
}
