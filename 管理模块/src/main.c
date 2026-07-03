#include "data/log.h"
#include "service/admin.h"
#include "view/admin_view.h"
#include <stdlib.h>
#include <stdio.h>

// 全局日志链表
LogList global_log_list;

int main()
{
    // 初始化日志链表 + 读取本地日志文件
    initLogList(&global_log_list);
    loadLogFromFile(&global_log_list);

    char login_name[20] = "admin";
    int mainOpt;

    // 简易主菜单循环，防止程序直接跑完退出
    while (1)
    {
        printf("\n===== 校园二手交易平台 - 管理模块测试 =====\n");
        printf("1. 进入管理员后台\n");
        printf("2. 查看个人操作日志\n");
        printf("0. 退出程序\n");
        printf("请输入功能序号：");
        scanf("%d", &mainOpt);

        if (mainOpt == 1)
        {
            if (isAdmin(login_name))
            {
                showAdminMenu(login_name);
            }
            else
            {
                printf("无管理员权限！\n");
                system("pause");
            }
        }
        else if (mainOpt == 2)
        {
            showUserLogMenu(login_name);
        }
        else if (mainOpt == 0)
        {
            printf("正在退出程序...\n");
            break;
        }
        else
        {
            printf("输入错误，请重新选择！\n");
            system("pause");
        }
        system("cls");
    }

    // 防闪退关键：程序结束前暂停
    printf("\n程序结束，按任意键关闭窗口...");
    system("pause");
    return 0;
}
