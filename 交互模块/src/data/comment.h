#ifndef COMMENT_H
#define COMMENT_H
#include "user.h"
#include "goods.h"

#define CID_LEN 20
#define COMMENT_CONTENT_LEN 200
#define TIME_LEN 30

typedef struct Comment {
    char cid[CID_LEN];
    char uid[USER_ID_LEN];
    char gid[GOODS_ID_LEN];
    char content[COMMENT_CONTENT_LEN];
    char time[TIME_LEN];
    struct Comment *next;
} Comment, *CommentList;

void InitCommentList(CommentList *L);

// 新增评论
int AddComment(CommentList *L, char *cid, char *uid, char *gid, char *content, char *time);

// 删除指定ID评论（仅本人可删）
int DelComment(CommentList *L, char *cid);

// 根据商品ID查询全部评论
Comment* SearchGoodsComment(CommentList L, char *gid);

// 根据评论ID查找单条评论
Comment* SearchCommentById(CommentList L, char *cid);

// 文件持久化
void SaveCommentToFile(CommentList L, const char *filePath);
void LoadCommentFromFile(CommentList *L, const char *filePath);

void FreeCommentList(CommentList *L);
#endif