#include <cstdlib>
#include <cassert>
#include <cstdio>
#include "dllist.h"

//------------------------------------
//! Allocates the memory for list_t
//!
//! \param  [in]    list    pointer to list
//!
//! \return pointer to list with allocated memory
//------------------------------------

list_t *listConstruct(list_t *list) {
    list = (list_t *) calloc(1, sizeof(list_t));
    assert(list);
    list->head = NULL;
    list->tail = NULL;
    ASSERT_LIST(list)
    return list;
}

//------------------------------------
//! Free the memory of the list
//!
//! \param  [in]    list     pointer to list
//------------------------------------

void listDestruct(list_t *list) {
    ASSERT_LIST(list)

    if (list->tail == list->head) {
        free(list->head);
    } else {
        free(list->head);
        free(list->tail);
    }
    free(list);
}

//-----------------------------------
//! Checks if the list is OK
//!
//! \param  [in]    list    pointer to list
//!
//! \return true, if pointer is not NULL
//-----------------------------------

bool listOK(list_t *list) {
    return list != NULL;
}

//-----------------------------------
//! Checks if the node is OK
//!
//! \param  [in]    node    pointer to node
//!
//! \return true, if pointer is not NULL
//-----------------------------------

bool nodeOK(node *elem) {
    return elem != NULL;
}

//------------------------------------
//! Pushes the node with data to the begin of list
//!
//! \param  [in]    list    list pointer
//! \param  [in]    data    data of new node
//------------------------------------

void listPush(list_t *list, double data) {
    ASSERT_LIST(list)

    node *elem = (node *) calloc(1, sizeof(node));
    assert(elem);
    elem->data = data;
    elem->prev = NULL;

    if (list->head != NULL) {
        elem->next = list->head;
        list->head->prev = elem;
        list->head = elem;
    } else {
        elem->next = NULL;
        list->head = list->tail = elem;
    }

    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the node to the begin of list
//!
//! \param  [in]    list    list pointer
//! \param  [in]    elem    pointer to node
//------------------------------------

void listPush(list_t *list, node *elem) {
    ASSERT_LIST(list)
    ASSERT_NODE(elem)

    elem->prev = NULL;

    if (list->head != NULL) {
        elem->next = list->head;
        list->head->prev = elem;
        list->head = elem;
    } else {
        elem->next = NULL;
        list->head = list->tail = elem;
    }

    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the node with data to the end of list
//!
//! \param  [in]    list    list pointer
//! \param  [in]    data    data of new node
//------------------------------------

void listPushBack(list_t *list, double data) {
    ASSERT_LIST(list);

    node *elem = (node *) calloc(1, sizeof(node));
    assert(elem);
    elem->data = data;
    elem->next = NULL;

    if (list->tail != NULL) {
        elem->prev = list->tail;
        list->tail->next = elem;
        list->tail = elem;
    } else {
        elem->prev = NULL;
        list->head = list->tail = elem;
    }

    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the node to the end of list
//!
//! \param  [in]    list    list pointer
//! \param  [in]    elem    pointer to node
//------------------------------------

void listPushBack(list_t *list, node *elem) {
    ASSERT_LIST(list)
    ASSERT_NODE(elem)

    elem->next = NULL;

    if (list->tail != NULL) {
        elem->prev = list->tail;
        list->tail->next = elem;
        list->tail = elem;
    } else {
        elem->prev = NULL;
        list->head = list->tail = elem;
    }

    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the new node with data after some node
//!
//! \param  [in]    list        list pointer
//! \param  [in]    listElem    pointer to some node
//! \param  [in]    data        data of new node
//------------------------------------

void listInsertAfter(list_t *list, node *listElem, double data) {
    ASSERT_LIST(list)
    ASSERT_NODE(listElem)

    if (listElem->next == NULL) {
        listPushBack(list, data);
    } else {
        node *elem = (node *) calloc(1, sizeof(node));
        assert(elem);
        elem->data = data;
        elem->next = listElem->next;
        elem->prev = listElem;
        elem->next->prev = elem;
        listElem->next = elem;
    }

    ASSERT_NODE(listElem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the new node after some node
//!
//! \param  [in]    list        list pointer
//! \param  [in]    listElem    pointer to some node
//! \param  [in]    elem        pointer to new node
//------------------------------------

void listInsertAfter(list_t *list, node *listElem, node *elem) {
    ASSERT_LIST(list);
    ASSERT_NODE(listElem)
    ASSERT_NODE(elem)

    if (listElem->next == NULL) {
        listPushBack(list, elem);
    } else {
        elem->next = listElem->next;
        elem->prev = listElem;
        elem->next->prev = elem;
        listElem->next = elem;
    }

    ASSERT_NODE(listElem)
    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the new node with data before some node
//!
//! \param  [in]    list        list pointer
//! \param  [in]    listElem    pointer to some node
//! \param  [in]    data        data of new node
//------------------------------------

void listInsertBefore(list_t *list, node *listElem, double data) {
    ASSERT_LIST(list)
    ASSERT_NODE(listElem)

    if (listElem->prev == NULL) {
        listPush(list, data);
    } else {
        node *elem = (node *) calloc(1, sizeof(node));
        assert(elem);
        elem->data = data;
        elem->next = listElem;
        elem->prev = listElem->prev;
        listElem->prev = elem;
        elem->prev->next = elem;
    }

    ASSERT_NODE(listElem)
    ASSERT_LIST(list)
}

//------------------------------------
//! Pushes the new node before some node
//!
//! \param  [in]    list        list pointer
//! \param  [in]    listElem    pointer to some node
//! \param  [in]    elem        pointer to new node
//------------------------------------

void listInsertBefore(list_t *list, node *listElem, node *elem) {
    ASSERT_LIST(list)
    ASSERT_NODE(listElem)
    ASSERT_NODE(elem)

    if (listElem->prev == NULL) {
        listPush(list, elem);
    } else {
        elem->next = listElem;
        elem->prev = listElem->prev;
        listElem->prev = elem;
        elem->prev->next = elem;
    }

    ASSERT_NODE(listElem)
    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------------
//! Pops the node from the begin
//!
//! \param  [in]    list    pointer to list
//------------------------------------------

void listPop(list_t *list) {
    ASSERT_LIST(list)

    if (list->head == list->tail && list->head != NULL) {
        free(list->head);
        list->head = list->tail = NULL;
    } else if (list->head != list->tail) {
        list->head = list->head->next;
        free(list->head->prev);
        list->head->prev = NULL;
    }

    ASSERT_LIST(list)
}

//------------------------------------------
//! Pops the node from the end
//!
//! \param  [in]    list    pointer to list
//------------------------------------------

void listPopBack(list_t *list) {
    ASSERT_LIST(list)

    if (list->head == list->tail && list->tail != NULL) {
        free(list->tail);
        list->head = list->tail = NULL;
    } else if (list->head != list->tail) {
        list->tail = list->tail->prev;
        free(list->tail->next);
        list->tail->next = NULL;
    }

    ASSERT_LIST(list)
}

//------------------------------------
//! Pops the elem from list
//!
//! \param  [in]    list    pointer to list
//! \param  [in]    elem    pointer to elem
//------------------------------------

void listPop(list_t *list, node *elem) {
    ASSERT_LIST(list)
    ASSERT_NODE(elem)

    if (elem->next == NULL) {
        listPopBack(list);
    } else if (elem->prev == NULL) {
        listPop(list);
    } else {
        elem->prev->next = elem->next;
        elem->next->prev = elem->prev;
        free(elem);
    }

    ASSERT_LIST(list)
}

//------------------------------------------
//! Pops the node after elem
//!
//! \param  [in]    list    pointer to list
//! \param  [in]    elem    pointer to elem
//------------------------------------------

void listPopAfter(list_t *list, node *elem) {
    ASSERT_LIST(list)
    ASSERT_NODE(elem)

    if (list->tail == elem->next) {
        elem = elem->next;
        listPop(list, elem);
    }

    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//------------------------------------------
//! Pops the node before elem
//!
//! \param  [in]    list    pointer to list
//! \param  [in]    elem    pointer to elem
//------------------------------------------

void listPopBefore(list_t *list, node *elem) {
    ASSERT_LIST(list)
    ASSERT_NODE(elem)

    if (list->head != elem) {
        elem = elem->prev;
        listPop(list, elem);
    }

    ASSERT_NODE(elem)
    ASSERT_LIST(list)
}

//-----------------------------------------
//! Prints the DUMP of list
//!
//! \param  [in]    list    pointer to list
//-----------------------------------------

void listDUMP(list_t *list) {
    if (list == NULL) {
        printf("list_t [%s%#010x%s] (ERROR!!!)\n", RED, list, RESET);
    } else {
        printf("list_t [%#010x] {\n", list);
        node *elem = list->head;
        while (elem) {
            printf("\t[%#010x] <- [%#010x] (%lf) -> [%#010x]\n", elem->prev, elem, elem->data, elem->next);
            elem = elem->next;
        }
        printf("}\n");
    }
}

//-----------------------------------------
//! Prints the DUMP of node
//!
//! \param  [in]    elem    pointer to node
//-----------------------------------------

void nodeDUMP(node *elem) {
    if (elem == NULL) {
        printf("node [%s%#010x%s] (%lf)\n", RED, elem, RESET, elem->data);
    } else {
        printf("node [%#010x] (%lf)\n", elem, elem->data);
    }
}

//-----------------------------------------
//! Finds the index of node with data
//!
//! \param  [in]    list    pointer to list
//! \param  [in]    data    data
//! \return index of node or -1 if no such node
//! \note It has empty loop, because we don't want you to use this function
//-----------------------------------------

int listFind(list_t *list, double data) {
    ASSERT_LIST(list)

    int index = 0;
    int result = -1;
    node *elem = list->head;

    while (elem) {
        for (int i = 0; i < 100000000; i++) {}
        if (elem->data == data) {
            result = index;
        }
        index++;
        elem = elem->next;
    }

    ASSERT_LIST(list)
    return result;
}