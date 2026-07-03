#ifndef INTER_VIEW_H
#define INTER_VIEW_H
#include "../service/inter_service.h"

// 交互总菜单（个人中心入口：我的收藏）
void View_InterMenu(CollectList *collectL, CommentList *comL, UserList userL, GoodsList goodsL, User loginUser);

// 收藏子菜单：收藏/查看/取消收藏
void View_CollectMenu(CollectList *collectL, GoodsList goodsL, User loginUser);

// 商品详情内评论面板：查看评论、发布评论、删除评论
void View_GoodsCommentPanel(CollectList *collectL, CommentList *comL, UserList userL, GoodsList goodsL, User loginUser, char *targetGid);
#endif