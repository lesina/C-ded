#include <cstring>
#include <cassert>
#include "differentiator.h"

//-------------------------------------------
//! Finds the differential
//! \param  [in]    n   pointer to the node
//-------------------------------------------

void d(node *n) {
    assert(n);
    if (n->type == NUMBER) {
        createNode(n, "0");
    } else if (n->type == VARIABLE) {
        createNode(n, "1");
    } else if (n->type == OPERATOR) {
        if (!strcmp(n->data, "+") || !strcmp(n->data, "-")) {
            d(n->left);
            d(n->right);
        } else if (!strcmp(n->data, "*")) {
            createNode(n, "+", n->left, n->right);
        }
    }
}

//-----------------------------------------------
//! Changes data of node
//! \param  [in]    n       pointer to the node
//! \param  [in]    data    new data of the node
//-----------------------------------------------

void createNode(node *n, nodeType data) {
    assert(n);
    n->data = data;
}

//-----------------------------------------------
//! changes data of node
//! \param  [in]    n       pointer to the node
//! \param  [in]    data    new data of the node
//! \param  [in]    left    left node of n
//! \param  [in]    right   right node of n
//-----------------------------------------------

void createNode(node *n, nodeType data, node *left, node *right) {
    assert(n);
    assert(left);
    assert(right);
    n->data = data;
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
    createNode(n, "cos");
    return n;
}

//----------------------------------------------------
//! Differentiates cos
//! \param  [in]    n   pointer to the node
//! \return new node
//----------------------------------------------------

node *diffCos(node *n) {
    assert(n);
    createNode(n, "*");
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

node *slozhna(node *n, node* (*diff)(node *)) {
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