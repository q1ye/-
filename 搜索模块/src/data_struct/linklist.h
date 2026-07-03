#ifndef LINKLIST_H
#define LINKLIST_H
#include <stddef.h>

typedef void* NodeData;
typedef struct Node {
    NodeData data;
    struct Node *next;
} Node, *LinkList;

LinkList list_create();
void list_append(LinkList head, NodeData data, size_t dataSize);
void list_destroy(LinkList head, void (*freeData)(NodeData));

#endif