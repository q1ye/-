#include "user.h"

void showMenu() {
    int op;
    while (1) {
        printf("\n====校园二手交易平台====\n");
        printf("1.用户注册  2.用户登录\n");
        printf("3.个人中心  0.退出程序\n");
        printf("请选择操作：");
        scanf("%d", &op);
        switch (op) {
            case 1:
                userRegister();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                if (loginUser == NULL) {
                    printf("未登录，请先登录！\n");
                } else {
                    printf("1.修改个人信息\n");
                    int sub;
                    scanf("%d", &sub);
                    if (sub == 1) modifyInfo();
                }
                break;
            case 0:
                freeAllUser();
                printf("程序退出\n");
                return;
            default:
                printf("输入错误，请重新选择！\n");
        }
    }
}

int main() {
    // 程序启动第一步：读取user.txt加载所有用户
    loadUserData();
    // 打开菜单
    showMenu();
    return 0;
}
