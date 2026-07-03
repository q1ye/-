#ifndef COMMENT_H
#define COMMENT_H
#include "user.h"
#include "goods.h"

#define COMMENT_CONTENT_LEN 300

typedef struct Comment
{
    char uid[UID_LEN];
    int goodsId;
    char content[COMMENT_CONTENT_LEN];
    char time[TIME_LEN];
    struct Comment* next;
} Comment, *CommentList;

void InitCommentList(CommentList* L);
void AddComment(CommentList* L, char* uid, int goodsId, char* content, char* time);
Comment* SearchCommentByGoodsId(CommentList L, int goodsId);
void SaveCommentToFile(CommentList L, const char* path);
void LoadCommentFromFile(CommentList* L, const char* path);
void FreeCommentList(CommentList* L);
#endif