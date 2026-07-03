#ifndef ADMIN_SERVICE_H
#define ADMIN_SERVICE_H

#include "../data/log.h"

// 仅保留日志链表，删除UndoStack、user_list、goods_list
extern LogList global_log_list;

// 1. 记录操作日志
void recordOperateLog(char* username, LogType op, char* target);

// 2. 管理员功能：查看全部日志
void showAllLog();
// 3. 用户功能：查看本人操作日志
void showUserLog(char* username);
// 4. 清空系统全部日志（管理员权限）
int adminClearLog();

// 屏蔽撤销操作接口
// int undoLastOperate();

// 5. 权限校验：判断账号是否为管理员
int isAdmin(char* username);

#endif