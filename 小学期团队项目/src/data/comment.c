#include "comment.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InitCommentList(CommentList* L)
{
    *L = (Comment*)malloc(sizeof(Comment));
    (*L)->next = NULL;
}

// 标准5参AddComment：L, uid(char*), goodsId(int), content(char*), time(char*)
void AddComment(CommentList* L, char* uid, int goodsId, char* content, char* time)
{
    Comment* newNode = (Comment*)malloc(sizeof(Comment));
    strncpy(newNode->uid, uid, UID_LEN - 1);
    newNode->uid[UID_LEN - 1] = '\0';

    newNode->goodsId = goodsId;

    strncpy(newNode->content, content, COMMENT_CONTENT_LEN - 1);
    newNode->content[COMMENT_CONTENT_LEN - 1] = '\0';

    strncpy(newNode->time, time, TIME_LEN - 1);
    newNode->time[TIME_LEN - 1] = '\0';
    newNode->next = NULL;

    Comment* p = *L;
    while (p->next != NULL)
        p = p->next;
    p->next = newNode;
}

Comment* SearchCommentByGoodsId(CommentList L, int goodsId)
{
    Comment* resHead = NULL, *resTail = NULL;
    Comment* p = L->next;
    while (p != NULL)
    {
        if (p->goodsId == goodsId)
        {
            Comment* temp = (Comment*)malloc(sizeof(Comment));
            *temp = *p;
            temp->next = NULL;
            if (resHead == NULL)
            {
                resHead = temp;
                resTail = temp;
            }
            else
            {
                resTail->next = temp;
                resTail = temp;
            }
        }
        p = p->next;
    }
    return resHead;
}

void SaveCommentToFile(CommentList L, const char* path)
{
    FILE* fp = fopen(path, "wb");
    if (!fp) return;
    Comment* p = L->next;
    while (p != NULL)
    {
        fwrite(p, sizeof(Comment), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

// 仅保留一份LoadCommentFromFile，删除重复副本
void LoadCommentFromFile(CommentList* L, const char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp) return;
    Comment temp;
    while (fread(&temp, sizeof(Comment), 1, fp) == 1)
    {
        // 修正：去掉无效cid/gid，仅传5个合法参数，数字用temp.goodsId
        AddComment(L, temp.uid, temp.goodsId, temp.content, temp.time);
    }
    fclose(fp);
}

// 仅保留一份FreeCommentList，删除重复副本
void FreeCommentList(CommentList* L)
{
    Comment* p = (*L)->next, *q;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}
