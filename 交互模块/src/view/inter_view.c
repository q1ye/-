#include "inter_view.h"

void View_InterMenu(CollectList *collectL, CommentList *comL, UserList userL, GoodsList goodsL, User loginUser) {
    int op;
    while(1) {
        printf("\n===== 用户交互中心 =====\n");
        printf("1. 查看我的收藏\n");
        printf("0. 返回上一级\n");
        printf("请输入操作：");
        scanf("%d", &op);
        getchar();

        if(op == 1) {
            View_CollectMenu(collectL, goodsL, loginUser);
        } else if(op == 0) {
            break;
        } else {
            printf("输入错误，请重新选择！\n");
        }
    }
}

void View_CollectMenu(CollectList *collectL, GoodsList goodsL, User loginUser) {
    int op;
    char gid[GOODS_ID_LEN];
    while(1) {
        printf("\n===== 收藏管理 =====\n");
        printf("1. 查看全部收藏\n");
        printf("2. 收藏新商品\n");
        printf("3. 取消收藏商品\n");
        printf("0. 返回\n");
        printf("选择操作：");
        scanf("%d", &op);
        getchar();

        if(op == 1) {
            Service_ShowMyCollect(*collectL, goodsL, loginUser);
        } else if(op == 2) {
            printf("输入要收藏的商品ID：");
            scanf("%s", gid);
            int ret = Service_CollectGoods(collectL, goodsL, loginUser, gid);
            if(ret == 1) printf("收藏成功！\n");
            else if(ret == 0) printf("你已收藏该商品\n");
            else printf("商品不存在\n");
        } else if(op == 3) {
            printf("输入要取消收藏的商品ID：");
            scanf("%s", gid);
            int ret = Service_CancelCollect(collectL, loginUser, gid);
            if(ret) printf("取消收藏成功\n");
            else printf("未收藏该商品\n");
        } else if(op == 0) {
            break;
        } else {
            printf("无效选项\n");
        }
    }
}

void View_GoodsCommentPanel(CollectList *collectL, CommentList *comL, UserList userL, GoodsList goodsL, User loginUser, char *targetGid) {
    int op;
    char content[COMMENT_CONTENT_LEN], cid[CID_LEN];
    while(1) {
        printf("\n===== 商品评论操作 =====\n");
        printf("1. 查看全部评论\n");
        printf("2. 发布评论\n");
        printf("3. 删除我的评论\n");
        printf("0. 返回商品页面\n");
        printf("选择：");
        scanf("%d", &op);
        getchar();

        if(op == 1) {
            Service_ShowGoodsComment(*comL, userL, targetGid);
        } else if(op == 2) {
            printf("输入评论内容：");
            fgets(content, COMMENT_CONTENT_LEN, stdin);
            // 去除换行符
            content[strcspn(content, "\n")] = '\0';
            int ret = Service_PublishComment(comL, goodsL, loginUser, targetGid, content);
            if(ret == 1) printf("评论发布成功！\n");
            else if(ret == -1) printf("商品不存在\n");
            else printf("评论内容不能为空\n");
        } else if(op == 3) {
            printf("输入要删除的评论ID：");
            scanf("%s", cid);
            int ret = Service_DeleteComment(comL, loginUser, cid);
            if(ret == 1) printf("删除成功\n");
            else if(ret == -1) printf("只能删除自己的评论\n");
            else printf("评论不存在\n");
        } else if(op == 0) {
            break;
        } else {
            printf("输入错误\n");
        }
    }
}
