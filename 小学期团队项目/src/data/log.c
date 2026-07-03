#include "log.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void initLogList(LogList* L)
{
    *L = (Log*)malloc(sizeof(Log));
    (*L)->next = NULL;
}

void addLog(LogList* L, char* uid, LogType op, char* msg)
{
    Log* newNode = (Log*)malloc(sizeof(Log));
    time_t t = time(NULL);
    strftime(newNode->opTime, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&t));
    strcpy(newNode->opUid, uid);
    strcpy(newNode->content, msg);
    newNode->next = NULL;

    Log* p = *L;
    while(p->next != NULL)
        p = p->next;
    p->next = newNode;
}

void showAllLog(LogList L)
{
    Log* p = L->next;
    if(p == NULL)
    {
        printf("暂无操作日志\n");
        return;
    }
    printf("====系统操作日志====\n");
    while(p)
    {
        printf("[%s] 用户%s：%s\n", p->opTime, p->opUid, p->content);
        p = p->next;
    }
}

void saveLogToFile(LogList L)
{
    FILE* fp = fopen("data/log.dat", "wb");
    if(!fp) return;
    Log* p = L->next;
    while(p)
    {
        fwrite(p, sizeof(Log), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void loadLogFromFile(LogList* L)
{
    FILE* fp = fopen("data/log.dat", "rb");
    if(!fp) return;
    Log temp;
    while(fread(&temp, sizeof(Log), 1, fp) == 1)
    {
        Log* newNode = (Log*)malloc(sizeof(Log));
        *newNode = temp;
        newNode->next = (*L)->next;
        (*L)->next = newNode;
    }
    fclose(fp);
}

void FreeLogList(LogList* L)
{
    Log* p = (*L)->next, *q;
    while(p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}
