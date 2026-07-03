#ifndef INTER_SERVICE_H
#define INTER_SERVICE_H
#include <time.h> // 修复time/strftime/localtime未声明
#include "../data/comment.h"
#include "../data/collect.h"
#include "../data/goods.h"
#include "../data/user.h"

char* GenCommentId();
int ServicePublishComment(CommentList* cList,User* login, int goodsId,char* text);
void ServiceShowGoodsComment(CommentList cList,int goodsId);
#endif