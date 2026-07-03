#ifndef LOG_H
#define LOG_H
#include "user.h"

// 日志操作枚举
typedef enum {
    LOG_USER_REG,
    LOG_GOODS_PUB,
    LOG_GOODS_EDIT,
    LOG_COMMENT,
    LOG_DELETE
} LogType;

#define LOG_CONTENT_LEN 512
typedef struct Log{
    char opUid[UID_LEN];
    char opTime[TIME_LEN];
    char content[LOG_CONTENT_LEN];
    struct Log* next;
}Log,*LogList;

void initLogList(LogList* L);
void addLog(LogList* L,char* uid,LogType op,char* msg);
void showAllLog(LogList L);
void saveLogToFile(LogList L);
void loadLogFromFile(LogList* L);
void FreeLogList(LogList* L);
#endif