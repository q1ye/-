#include "log.h"

void initLogList(LogList* head) {
    *head = (LogList)malloc(sizeof(LogNode));
    (*head)->next = NULL;
}

void getNowTime(char* time_buf) {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    strftime(time_buf, 30, "%Y-%m-%d %H:%M:%S", tm);
}

char* getLogTypeText(LogType type) {
    switch (type) {
        case LOG_USER_REG: return "用户注册";
        case LOG_GOODS_PUB: return "发布商品";
        case LOG_GOODS_EDIT: return "修改商品";
        case LOG_GOODS_OFF: return "商品下架";
        case LOG_COMMENT_ADD: return "新增评论";
        case LOG_GOODS_DEL: return "删除商品";
        case LOG_USER_MOD: return "修改个人信息";
        default: return "未知操作";
    }
}

void addLogNode(LogList* head, LogNode log) {
    LogNode* new_node = (LogNode*)malloc(sizeof(LogNode));
    *new_node = log;
    new_node->next = (*head)->next;
    (*head)->next = new_node;
}

// 将日志写入data/log.dat
void saveLogToFile(LogList head) {
    FILE* fp = fopen("data/log.dat", "wb");
    if (!fp) {
        printf("日志文件打开失败！\n");
        return;
    }
    LogNode* p = head->next;
    while (p) {
        fwrite(p, sizeof(LogNode), 1, fp);
        p = p->next;
    }
    fclose(fp);
}

// 程序启动读取本地日志文件
void loadLogFromFile(LogList* head) {
    FILE* fp = fopen("data/log.dat", "rb");
    if (!fp) return;
    LogNode temp;
    while (fread(&temp, sizeof(LogNode), 1, fp) == 1) {
        addLogNode(head, temp);
    }
    fclose(fp);
}

void clearAllLog(LogList* head) {
    LogNode* p = (*head)->next, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q);
    }
    (*head)->next = NULL;
    saveLogToFile(*head);
}

// 屏蔽撤销栈全部实现
/*
void initUndoStack(UndoStack* stack) {
    *stack = NULL;
}

void pushUndo(UndoStack* stack, void* data, LogType type) {
    UndoStackNode* new_node = (UndoStackNode*)malloc(sizeof(UndoStackNode));
    new_node->op_type = type;
    size_t data_size = 0;
    if (type == LOG_GOODS_DEL || type == LOG_GOODS_EDIT) data_size = sizeof(Goods);
    else if (type == LOG_USER_MOD) data_size = sizeof(User);
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->next = *stack;
    *stack = new_node;
}

int popUndo(UndoStack* stack, void* out_data, LogType* out_type) {
    if (*stack == NULL) return 0;
    UndoStackNode* top = *stack;
    *out_type = top->op_type;
    size_t data_size = 0;
    if (top->op_type == LOG_GOODS_DEL || top->op_type == LOG_GOODS_EDIT) data_size = sizeof(Goods);
    else if (top->op_type == LOG_USER_MOD) data_size = sizeof(User);
    memcpy(out_data, top->data, data_size);
    free(top->data);
    *stack = top->next;
    free(top);
    return 1;
}

void freeUndoStack(UndoStack* stack) {
    UndoStackNode* p = *stack, *q;
    while (p) {
        q = p;
        p = p->next;
        free(q->data);
        free(q);
    }
    *stack = NULL;
}
*/
