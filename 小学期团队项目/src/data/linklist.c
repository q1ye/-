#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkList list_create() {
    LinkList head = (LinkList)malloc(sizeof(Node));
    if (!head) {
        perror("list create malloc fail");
        exit(1);
    }
    head->next = NULL;
    return head;
}

void list_append(LinkList head, NodeData data, size_t dataSize) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("node malloc fail");
        return;
    }
    newNode->data = malloc(dataSize);
    memcpy(newNode->data, data, dataSize);
    newNode->next = NULL;

    Node *p = head;
    while (p->next) p = p->next;
    p->next = newNode;
}

void list_destroy(LinkList head, void (*freeData)(NodeData)) {
    Node *p = head, *q;
    while (p) {
        q = p;
        p = p->next;
        if (freeData && q->data) {
            freeData(q->data);
        }
        free(q);
    }
}
