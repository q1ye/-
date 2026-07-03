#include "inter_service.h"

void GenCommentId(char *cidBuf) {
    time_t t = time(NULL);
    sprintf(cidBuf, "C%lld", t);
}

int Service_CollectGoods(CollectList *collectL, GoodsList goodsL, User loginUser, char *gid) {
    // 校验1：商品是否存在
    Goods *g = SearchGoodsById(goodsL, gid);
    if (!g) return -1;
    // 校验2：是否已收藏
    if (IsCollected(*collectL, loginUser.uid, gid)) return 0;
    // 添加收藏
    AddCollect(collectL, loginUser.uid, gid);
    return 1;
}

int Service_CancelCollect(CollectList *collectL, User loginUser, char *gid) {
    return DelCollect(collectL, loginUser.uid, gid);
}

void Service_ShowMyCollect(CollectList collectL, GoodsList goodsL, User loginUser) {
    Collect *p = collectL->next;
    int has = 0;
    printf("===== 我的收藏列表 =====\n");
    while(p) {
        if(strcmp(p->uid, loginUser.uid) == 0) {
            Goods *g = SearchGoodsById(goodsL, p->gid);
            if(g) {
                has = 1;
                printf("商品ID：%s | 名称：%s | 价格：%.2lf\n", g->gid, g->name, g->price);
            }
        }
        p = p->next;
    }
    if(!has) printf("暂无收藏商品\n");
}

int Service_PublishComment(CommentList *comL, GoodsList goodsL, User loginUser, char *gid, char *content) {
    Goods *g = SearchGoodsById(goodsL, gid);
    if (!g) return -1;
    if (strlen(content) == 0) return -2;

    char cid[CID_LEN], nowTime[TIME_LEN];
    GenCommentId(cid);
    time_t t = time(NULL);
    strftime(nowTime, TIME_LEN, "%Y-%m-%d %H:%M:%S", localtime(&t));
    AddComment(comL, cid, loginUser.uid, gid, content, nowTime);
    return 1;
}

int Service_DeleteComment(CommentList *comL, User loginUser, char *cid) {
    Comment *c = SearchCommentById(*comL, cid);
    if (!c) return 0;
    // 仅评论本人可删除
    if (strcmp(c->uid, loginUser.uid) != 0) return -1;
    return DelComment(comL, cid);
}

void Service_ShowGoodsComment(CommentList comL, UserList userL, char *gid) {
    Comment *p = comL->next;
    int has = 0;
    printf("===== 商品评论区 =====\n");
    while(p) {
        if(strcmp(p->gid, gid) == 0) {
            has = 1;
            User *u = SearchUserById(userL, p->uid);
            char uname[USER_NAME_LEN] = "匿名用户";
            if(u) strcpy(uname, u->username);
            printf("[%s] %s 说：%s (评论ID:%s)\n", p->time, uname, p->content, p->cid);
        }
        p = p->next;
    }
    if(!has) printf("该商品暂无评论\n");
}
