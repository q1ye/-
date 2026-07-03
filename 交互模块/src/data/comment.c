#include "comment.h"

void InitCommentList(CommentList *L) {
    *L = (Comment*)malloc(sizeof(Comment));
    (*L)->next = NULL;
}

int AddComment(CommentList *L, char *cid, char *uid, char *gid, char *content, char *time) {
    Comment *newNode = (Comment*)malloc(sizeof(Comment));
    strcpy(newNode->cid, cid);
    strcpy(newNode->uid, uid);
    strcpy(newNode->gid, gid);
    strcpy(newNode->content, content);
    strcpy(newNode->time, time);
    newNode->next = (*L)->next;
    (*L)->next = newNode;
    return 1;
}

int DelComment(CommentList *L, char *cid) {
    Comment *pre = *L, *p = pre->next;
    while(p) {
        if(strcmp(p->cid, cid) == 0) {
            pre->next = p->next;
            free(p);
            return 1;
        }
        pre = p;
        p = p->next;
    }
    return 0;
}

Comment* SearchGoodsComment(CommentList L, char *gid) {
    return L->next;
}

Comment* SearchCommentById(CommentList L, char *cid) {
    Comment *p = L->next;
    while(p) {
        if(strcmp(p->cid, cid) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void SaveCommentToFile(CommentList L, const char *filePath) {
    FILE *fp = fopen(filePath, "wb");
    if (!fp) return;
    Comment *p = L->next;
    while (p) {
        fwrite(p, sizeof(Comment), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

void LoadCommentFromFile(CommentList *L, const char *filePath) {
    FILE *fp = fopen(filePath, "rb");
    if (!fp) return;
    Comment temp;
    while (fread(&temp, sizeof(Comment), 1, fp) == 1) {
        AddComment(L, temp.cid, temp.uid, temp.gid, temp.content, temp.time);
    }
    fclose(fp);
}

void FreeCommentList(CommentList *L) {
    Comment *p = (*L)->next, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    free(*L);
    *L = NULL;
}
