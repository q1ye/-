#include "admin.h"

void recordOperateLog(char* username, LogType op, char* target) {
    LogNode log;
    strcpy(log.username, username);
    log.op_type = op;
    strcpy(log.target_info, target);
    getNowTime(log.op_time);
    addLogNode(&global_log_list, log);
    saveLogToFile(global_log_list);
}

void showAllLog() {
    LogNode* p = global_log_list->next;
    if (!p) {
        printf("暂无系统操作日志\n");
        return;
    }
    printf("===== 全量系统操作日志 =====\n");
    while (p) {
        printf("操作人：%s | 操作：%s | 对象：%s | 时间：%s\n",
               p->username, getLogTypeText(p->op_type), p->target_info, p->op_time);
        p = p->next;
    }
}

void showUserLog(char* username) {
    LogNode* p = global_log_list->next;
    int has_log = 0;
    printf("===== 个人操作日志 =====\n");
    while (p) {
        if (strcmp(p->username, username) == 0) {
            has_log = 1;
            printf("操作：%s | 对象：%s | 时间：%s\n",
                   getLogTypeText(p->op_type), p->target_info, p->op_time);
        }
        p = p->next;
    }
    if (!has_log) printf("暂无个人操作记录\n");
}

int adminClearLog() {
    clearAllLog(&global_log_list);
    return 1;
}

// 屏蔽撤销函数，无User/Goods无法实现
/*
int undoLastOperate() {
    LogType op_type;
    void* temp_data;
    Goods temp_goods;
    User temp_user;
    int ret = popUndo(&global_undo_stack, &temp_goods, &op_type);
    if (!ret) {
        printf("无操作可撤销！\n");
        return 0;
    }
    switch (op_type) {
        case LOG_GOODS_DEL:
            addGoods(&goods_list, temp_goods);
            printf("撤销删除商品成功，商品已恢复\n");
            break;
        case LOG_GOODS_EDIT:
            updateGoods(&goods_list, temp_goods);
            printf("撤销商品修改，数据恢复原始状态\n");
            break;
        case LOG_USER_MOD:
            memcpy(&temp_user, temp_data, sizeof(User));
            updateUser(&user_list, temp_user);
            printf("撤销用户信息修改\n");
            break;
        default:
            printf("当前操作不支持撤销\n");
    }
    saveGoodsToFile(goods_list);
    saveUserToFile(user_list);
    recordOperateLog("system", op_type, "执行撤销回滚");
    return 1;
}
*/

int isAdmin(char* username) {
    if (strcmp(username, "admin") == 0) return 1;
    return 0;
}
