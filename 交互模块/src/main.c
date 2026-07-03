#include "data/user.h"
#include "data/goods.h"
#include "data/collect.h"
#include "data/comment.h"
#include "service/inter_service.h"
#include "view/inter_view.h"

int main() {
    // 1. 定义所有链表
    UserList userList;
    GoodsList goodsList;
    CollectList collectList;
    CommentList commentList;
    User loginUser; // 当前登录用户

    // 2. 初始化
    InitUserList(&userList);
    InitGoodsList(&goodsList);
    InitCollectList(&collectList);
    InitCommentList(&commentList);

    // 3. 加载持久化文件数据
    LoadUserFromFile(&userList, "file/user.dat");
    LoadGoodsFromFile(&goodsList, "file/goods.dat");
    LoadCollectFromFile(&collectList, "file/collect.dat");
    LoadCommentFromFile(&commentList, "file/comment.dat");

    // 模拟登录逻辑省略...登录成功后赋值loginUser

    // 进入交互中心菜单
    View_InterMenu(&collectList, &commentList, userList, goodsList, loginUser);

    // 程序退出前保存数据
    SaveUserToFile(userList, "file/user.dat");
    SaveGoodsToFile(goodsList, "file/goods.dat");
    SaveCollectToFile(collectList, "file/collect.dat");
    SaveCommentToFile(commentList, "file/comment.dat");

    // 释放内存
    FreeUserList(&userList);
    FreeGoodsList(&goodsList);
    FreeCollectList(&collectList);
    FreeCommentList(&commentList);
    return 0;
}
