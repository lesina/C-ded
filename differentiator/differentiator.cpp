#include <cstring>
#include <cassert>
#include <stdlib.h>
#include <iostream>
#include "differentiator.h"

enum answer {
    OPTIMIZED = 0,
    OPTIMIZING
};

//-------------------------------------------
//! Finds the differential
//! \param  [in]    n   pointer to the node
//-------------------------------------------

void d(node *n) {
    assert(n);
    if (n->type == NUMBER) {
        createNode(n, "0", NUMBER);
    } else if (n->type == VARIABLE) {
        createNode(n, "1", NUMBER);
    } else if (n->type == OPERATOR) {
        if (!strcmp(n->data, "+") || !strcmp(n->data, "-")) {
            d(n->left);
            d(n->right);
        } else if (!strcmp(n->data, "*")) {
            createNodeMul(n, "+", n->left, n->right, OPERATOR);
        } else if (!strcmp(n->data, "sin")) {
            n = difficultFunc(n, diffSin);
        } else if (!strcmp(n->data, "cos")) {
            n = difficultFunc(n, diffCos);
        }
    }
}

//-----------------------------------------------
//! Changes data of node
//! \param  [in]    n       pointer to the node
//! \param  [in]    data    new data of the node
//-----------------------------------------------

void createNode(node *n, nodeType data, int type) {
    assert(n);
    n->data = data;
    n->type = type;
}

//-----------------------------------------------
//! changes data of node
//! \param  [in]    n       pointer to the node
//! \param  [in]    data    new data of the node
//! \param  [in]    left    left node of n
//! \param  [in]    right   right node of n
//-----------------------------------------------

void createNodeMul(node *n, nodeType data, node *left, node *right, int type) {
    assert(left);
    assert(right);
    createNode(n, data, type);
    node *CL = copy(left);
    node *CR = copy(right);
    n->left = nodeConstruct(n->left, "*");
    n->right = nodeConstruct(n->right, "*");
    d(right);
    d(left);
    n->left->left = CL;
    n->left->right = right;
    n->right->right = CR;
    n->right->left = left;
}

//---------------------------------------------------
//! Makes copy of node
//! \param  [in]    n   pointer to the node
//! \return copy of node
//---------------------------------------------------

node *copy(node *n) {
    assert(n);
    node *newNode = NULL;
    newNode = nodeConstruct(newNode, n->data);
    newNode->left = n->left;
    newNode->right = n->right;
    return newNode;
}

//----------------------------------------------------
//! Differentiates sin
//! \param  [in]    n   pointer to the node
//! \return new node
//----------------------------------------------------

node *diffSin(node *n) {
    assert(n);
    createNode(n, "cos", OPERATOR);
    return n;
}

//----------------------------------------------------
//! Differentiates cos
//! \param  [in]    n   pointer to the node
//! \return new node
//----------------------------------------------------

node *diffCos(node *n) {
    assert(n);
    createNode(n, "*", OPERATOR);
    node *cL = copy(n->left);
    n->left = nodeConstruct(n->left, "-1");
    n->right = nodeConstruct(n->right, "sin");
    n->right->left = cL;
    return n;
}

//----------------------------------------------------
//! Differentiates difficult function
//! \param  [in]    n       pointer to the node
//! \param  [in]    diff    differential function
//! \return result of differential
//----------------------------------------------------

node *difficultFunc(node *n, node *(*diff)(node *)) {
    assert(n);
    assert(diff);
    node *mul = nodeConstruct(mul, "*");
    mul->right = diff(n);
    d(n->left);
    mul->left = n->left;
    return mul;
}

//-----------------------------------------------------
//! Prints result of differential
//! \param  [in]    tree    pointer to the tree
//-----------------------------------------------------

void printResult(binTree *tree) {
    assert(tree);
    node *elem = tree->root;
    if (!elem) return;
    tree->root = elem->left;
    printResult(tree);
    printf("%s", elem->data);
    tree->root = elem->right;
    printResult(tree);
    tree->root = elem;
}

//---------------------------------------------------
//! Simplifies the tree
//! \param  [in]    n   pointer to the node
//---------------------------------------------------

void optimizer(node *n) {
    assert(n);
    int *status = (int *) calloc(1, sizeof(int));
    do {
        *status = OPTIMIZED;
        calculate(n, status);
        calculateConst(n, status);
    } while (*status);
}

//--------------------------------------------------
//! Simplifies simple expressions
//! \param  [in]    n       pointer to the node
//! \param  [in]    status  pointer to the status of simplifying
//--------------------------------------------------

void calculate(node *n, int *status) {
    assert(status);
    node *elem = n;
    if (!elem->left || !elem->right) return;
    n = n->left;
    calculate(n, status);
    n = elem;
    if ((!(strcmp(n->left->data, "0")) || !(strcmp(n->right->data, "0"))) && (!strcmp(n->data, "*"))) {
        createNode(n, "0", NUMBER);
        n->left = NULL;
        n->right = NULL;
        *status = OPTIMIZING;
    } else if ((!(strcmp(n->left->data, "1")) && (!strcmp(n->data, "*"))) ||
               (!(strcmp(n->left->data, "0")) && (!strcmp(n->data, "+")))) {
        createNode(n, n->right->data, n->right->type);
        n->left = n->right->left;
        n->right = n->right->right;
        *status = OPTIMIZING;
    } else if ((!(strcmp(n->right->data, "1")) && (!strcmp(n->data, "*"))) ||
               (!(strcmp(n->right->data, "0")) && (!strcmp(n->data, "+"))) ||
               (!(strcmp(n->right->data, "0")) && (!strcmp(n->data, "-")))) {
        createNode(n, n->left->data, n->left->type);
        n->right = n->left->right;
        n->left = n->left->left;
        *status = OPTIMIZING;
    } else if (!(strcmp(n->left->data, "0")) && (!strcmp(n->data, "-"))) {
        createNode(n, "*", OPERATOR);
        createNode(n->left, "-1", NUMBER);
        *status = OPTIMIZING;
    }
    if (!elem->left || !elem->right) return;
    n = n->right;
    calculate(n, status);
    n = elem;
}

//--------------------------------------------------
//! Simplifying two NUMBER nodes
//! \param  [in]    n       pointer to the node
//! \param  [in]    status  pointer to the status of simplifying
//--------------------------------------------------

void calculateConst(node *n, int *status) {
    assert(status);
    node *elem = n;
    if (!elem->left || !elem->right) return;
    n = n->left;
    calculate(n, status);
    n = elem;
    if (n->left->type == NUMBER && n->right->type == NUMBER) {
        int a;
        int b;
        a = atoi(n->left->data);
        b = atoi(n->right->data);
        if (!strcmp(n->data, "*")) {
            sprintf(n->data, "%d", a*b);
            n->left = n->right = NULL;
        } else if (!strcmp(n->data, "+")) {
            sprintf(n->data, "%d", a+b);
            n->left = n->right = NULL;
        } else if (!strcmp(n->data, "-")) {
            sprintf(n->data, "%d", a-b);
            n->left = n->right = NULL;
        }
        n->type = NUMBER;
        *status = OPTIMIZING;
    }
    if (!elem->left || !elem->right) return;
    n = n->right;
    calculate(n, status);
    n = elem;
}