#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 操作类型枚举：区分所有系统行为
typedef enum {
    LOG_USER_REG,    // 用户注册
    LOG_GOODS_PUB,   // 发布商品
    LOG_GOODS_EDIT,  // 修改商品
    LOG_GOODS_OFF,   // 商品下架
    LOG_COMMENT_ADD, // 新增评论
    LOG_GOODS_DEL,   // 删除商品
    LOG_USER_MOD     // 修改个人信息
} LogType;

// 单条日志结构体
typedef struct Log {
    char username[20];    // 操作人账号
    LogType op_type;      // 操作类型
    char target_info[50];  // 操作对象（商品名/用户ID）
    char op_time[30];     // 操作时间
    struct Log* next;     // 日志链表节点
} LogNode, *LogList;

// 注释撤销栈相关定义（无User/Goods结构体，暂时屏蔽）
/*
typedef struct UndoStackNode {
    void* data;
    LogType op_type;
    struct UndoStackNode* next;
} UndoStackNode, *UndoStack;
*/

// 链表全局操作
void initLogList(LogList* head);
void addLogNode(LogList* head, LogNode log);
void loadLogFromFile(LogList* head);
void saveLogToFile(LogList head);
void clearAllLog(LogList* head);

// 注释撤销栈接口
/*
void initUndoStack(UndoStack* stack);
void pushUndo(UndoStack* stack, void* data, LogType type);
int popUndo(UndoStack* stack, void* out_data, LogType* out_type);
void freeUndoStack(UndoStack* stack);
*/

// 工具函数
void getNowTime(char* time_buf);
char* getLogTypeText(LogType type);

#endif