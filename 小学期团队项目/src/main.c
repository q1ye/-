#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 数据层
#include "data/log.h"
#include "data/user.h"
#include "data/goods.h"
#include "data/collect.h"
#include "data/comment.h"
#include "data/file_io.h"

// 业务层
#include "service/admin.h"
#include "service/user_service.h"
#include "service/goods_service.h"
#include "service/search.h"
#include "service/inter_service.h"

// 界面层
#include "view/admin_view.h"
#include "view/user_view.h"
#include "view/goods_view.h"
#include "view/search_view.h"
#include "view/inter_view.h"

// 全局链表
LogList global_log_list;
UserList userList;
GoodsList goodsList;
CollectList collectList;
CommentList commentList;
User* loginUser = NULL;

int main()
{
    // 初始化全部链表
    initLogList(&global_log_list);
    loadLogFromFile(&global_log_list);

    InitUserList(&userList);
    LoadUserFromFile(&userList, "data/user.dat");

    InitGoodsList(&goodsList);
    LoadGoodsFromFile(&goodsList, "data/goods.dat");

    InitCollectList(&collectList);
    LoadCollectFromFile(&collectList, "data/collect.dat");

    InitCommentList(&commentList);
    LoadCommentFromFile(&commentList, "data/comment.dat");

    int opt;
    while (1)
    {
        system("cls");
        printf("====校园二手交易平台总菜单====\n");
        printf("1 用户中心  2 商品中心  3 商品搜索\n");
        printf("4 评论收藏  5 管理员后台 0 退出\n");
        printf("请输入序号：");
        scanf("%d", &opt);
        switch(opt)
        {
            case 1:
                showUserView(userList, &loginUser);
                break;
            case 2:
                if(!loginUser){printf("请先登录！\n");system("pause");break;}
                showGoodsView(loginUser, goodsList);
                break;
            case 3:
                showSearchView(goodsList);
                break;
            case 4:
                if(!loginUser){printf("请先登录！\n");system("pause");break;}
                showInterView(&collectList, &commentList, userList, goodsList, loginUser);
                break;
            case 5:
                if(loginUser && strcmp(loginUser->uid, "admin")==0)
                    showAdminView(global_log_list);
                else printf("权限不足\n");
                system("pause");
                break;
            case 0:
                // 保存全部数据
                saveLogToFile(global_log_list);
                SaveUserToFile(userList, "data/user.dat");
                saveGoodsToFile(goodsList);
                SaveCollectToFile(collectList, "data/collect.dat");
                SaveCommentToFile(commentList, "data/comment.dat");
                // 释放内存
                FreeLogList(&global_log_list);
                FreeUserList(&userList);
                freeAllGoods();
                FreeCollectList(&collectList);
                FreeCommentList(&commentList);
                goto exit_main;
            default:
                printf("输入错误\n");
                system("pause");
        }
    }
exit_main:
    printf("程序退出，按任意键关闭窗口\n");
    system("pause");
    return 0;
}
