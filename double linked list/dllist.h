#ifndef DOUBLE_LINKED_LIST_DLLIST_H
#define DOUBLE_LINKED_LIST_DLLIST_H

#define ASSERT_LIST(list) if (!listOK(list)) { listDUMP(list); exit(-1); }
#define ASSERT_NODE(node) if (!nodeOK(node)) { nodeDUMP(node); exit(-1); }
#define RED             "\033[1;31m"
#define RESET           "\033[0m"

struct node {
    double data;
    node *next, *prev;
};

struct list_t {
    node *head, *tail;
};

list_t *listConstruct(list_t *);

void listDestruct(list_t *);

void listPush(list_t *, double);

void listPushBack(list_t *, double);

void listInsertAfter(list_t *, node *, double);

void listInsertBefore(list_t *, node *, double);

void listPush(list_t *, node *);

void listPushBack(list_t *, node *);

void listInsertAfter(list_t *, node *, node *);

void listInsertBefore(list_t *, node *, node *);

void listPop(list_t *);

void listPop(list_t *, node *);

void listPopBack(list_t *);

void listPopAfter(list_t *, node *);

void listPopBefore(list_t *, node *);

bool listOK(list_t *);

bool nodeOK(node *);

void listDUMP(list_t *);

void nodeDUMP(node *);

int listFind(list_t *, double);

#endif //DOUBLE_LINKED_LIST_DLLIST_H
