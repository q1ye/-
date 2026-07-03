#ifndef ADMIN_H
#define ADMIN_H
#include "../data/log.h"

// 记录操作日志
void recordOperateLog(char* username, LogType op, char* target);
// 展示全部系统日志
void showAllSystemLog(LogList logList);
// 清空所有日志
void adminClearLog(LogList* logList);
// 根据用户筛选日志
void showUserLog(LogList logList, char* username);
// 获取操作类型文本
char* getLogTypeText(LogType op);

#endif