#ifndef INTER_SERVICE_H
#define INTER_SERVICE_H
#include "../data/collect.h"
#include "../data/comment.h"
#include "../data/user.h"
#include "../data/goods.h"

// 收藏业务
// 收藏商品：返回1成功 0失败
int Service_CollectGoods(CollectList *collectL, GoodsList goodsL, User loginUser, char *gid);
// 取消收藏
int Service_CancelCollect(CollectList *collectL, User loginUser, char *gid);
// 打印当前用户全部收藏商品
void Service_ShowMyCollect(CollectList collectL, GoodsList goodsL, User loginUser);

// 评论业务
// 发布商品评论，自动生成时间
int Service_PublishComment(CommentList *comL, GoodsList goodsL, User loginUser, char *gid, char *content);
// 删除自己的评论
int Service_DeleteComment(CommentList *comL, User loginUser, char *cid);
// 展示某商品所有评论+评论人昵称
void Service_ShowGoodsComment(CommentList comL, UserList userL, char *gid);

// 工具函数：生成唯一评论ID
void GenCommentId(char *cidBuf);
#endif