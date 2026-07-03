#include "admin.h"
#include <stdio.h>
#include <string.h>

char* getLogTypeText(LogType op)
{
    switch(op)
    {
        case LOG_USER_REG: return "用户注册";
        case LOG_GOODS_PUB: return "发布商品";
        case LOG_GOODS_EDIT: return "编辑商品";
        case LOG_COMMENT: return "发表评论";
        case LOG_DELETE: return "删除操作";
        default: return "未知操作";
    }
}

void recordOperateLog(char* username, LogType op, char* target)
{
    char msg[LOG_CONTENT_LEN];
    char* opText = getLogTypeText(op);
    snprintf(msg, LOG_CONTENT_LEN, "%s：%s", opText, target);
    extern LogList global_log_list;
    addLog(&global_log_list, username, op, msg);
}

void showAllSystemLog(LogList logList)
{
    printf("==========全部系统操作日志==========\n");
    Log* p = logList->next;
    if(!p)
    {
        printf("暂无日志记录\n");
        return;
    }
    while(p)
    {
        printf("[%s] 操作者：%s 内容：%s\n", p->opTime, p->opUid, p->content);
        p = p->next;
    }
}

void showUserLog(LogList logList, char* username)
{
    printf("==========用户 %s 的操作日志==========\n", username);
    Log* p = logList->next;
    int hasLog = 0;
    while(p)
    {
        if(strcmp(p->opUid, username) == 0)
        {
            hasLog = 1;
            printf("[%s] %s\n", p->opTime, p->content);
        }
        p = p->next;
    }
    if(!hasLog) printf("该用户无操作日志\n");
}

void adminClearLog(LogList* logList)
{
    FreeLogList(logList);
    initLogList(logList);
    printf("所有日志已清空\n");
}
