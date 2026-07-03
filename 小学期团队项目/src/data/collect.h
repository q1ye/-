#ifndef COLLECT_H
#define COLLECT_H
#include "user.h"
#include "goods.h"

#define COLLECT_UID_LEN 20
#define COLLECT_GID_LEN 20

// 收藏结构体：用户ID+商品ID唯一绑定
typedef struct Collect {
    char uid[COLLECT_UID_LEN];
    char gid[COLLECT_GID_LEN];
    struct Collect *next;
} Collect, *CollectList;

// 初始化收藏链表头结点
void InitCollectList(CollectList *L);

// 添加收藏记录
int AddCollect(CollectList *L, char *uid, char *gid);

// 取消收藏（删除记录）
int DelCollect(CollectList *L, char *uid, char *gid);

// 根据用户ID查询所有收藏
Collect* SearchUserCollect(CollectList L, char *uid);

// 判断用户是否已收藏该商品
int IsCollected(CollectList L, char *uid, char *gid);

// 持久化：保存收藏到文件
void SaveCollectToFile(CollectList L, const char *filePath);

// 持久化：从文件加载收藏数据
void LoadCollectFromFile(CollectList *L, const char *filePath);

// 释放收藏链表内存
void FreeCollectList(CollectList *L);
#endif