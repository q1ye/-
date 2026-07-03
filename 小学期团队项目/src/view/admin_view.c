#include "admin_view.h"
#include "../service/admin.h"

void showAdminMenu(char* login_user) {
    int opt;
    while (1) {
        printf("\n========== 系统管理后台 ==========\n");
        printf("1. 查看全部操作日志\n");
        printf("2. 清空所有系统日志\n");
        printf("0. 返回主菜单\n");
        printf("请输入操作：");
        scanf("%d", &opt);
        switch(opt) {
            case 1:
                showAllLog();
                break;
            case 2:
                adminClearLog();
                printf("日志已全部清空\n");
                break;
            case 0:
                return;
            default:
                printf("输入错误，请重新选择\n");
        }
    }
}

void showUserLogMenu(char* login_user) {
    printf("\n===== 个人操作记录 =====\n");
    showUserLog(login_user);
    system("pause");
}
