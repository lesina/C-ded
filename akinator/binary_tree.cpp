#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include "binary_tree.h"

//---------------------------------------
//! Allocates the memory for tree
//! \param  [in]    tree    pointer to binary tree
//! \return tree with allocated memory
//---------------------------------------

binTree *treeConstruct(binTree *tree) {
    tree = (binTree *) calloc(1, sizeof(binTree));
    assert(tree);
    tree->root = NULL;
    tree->number_of_nodes = 0;
    tree->counter = 0;
    return tree;
}

//---------------------------------------
//! Allocates the memory for tree with data root
//! \param  [in]    tree    pointer to binary tree
//! \param  [in]    data    data of the root
//! \return tree with allocated memory
//---------------------------------------

binTree *treeConstruct(binTree *tree, double data) {
    tree = (binTree *) calloc(1, sizeof(binTree));
    assert(tree);
    tree->root = nodeConstruct(tree->root, data);
    tree->number_of_nodes = 1;
    tree->counter = 0;
    return tree;
}

//---------------------------------------
//! Allocates the memory for tree with root=elem
//! \param  [in]    tree    pointer to binary tree
//! \param  [in]    elem    pointer to elem
//! \return tree with allocated memory
//---------------------------------------

binTree *treeConstruct(binTree *tree, node *elem) {
    assert(elem);
    tree = (binTree *) calloc(1, sizeof(binTree));
    assert(tree);
    tree->root = elem;
    tree->number_of_nodes = 1;
    tree->counter = 0;
    return tree;
}

//-------------------------------------------
//! Allocates the memory for node with data
//! \param  [in]    elem    pointer to elem
//! \param  [in]    data    data of the elem
//! \return node with data
//-------------------------------------------

node *nodeConstruct(node *elem, double data) {
    elem = (node *) calloc(1, sizeof(node));
    assert(elem);
    elem->data = data;
    elem->left = NULL;
    elem->right = NULL;
    return elem;
}

//-----------------------------------------
//! Free the memory of every node and tree
//! \param  [in]    tree    pointer to tree
//! \note the algorithm is recursive
//-----------------------------------------

void treeDestruct(binTree *tree) {
    ASSERT_OK(tree)
    node *elem = tree->root;
    if (!elem) return;
    tree->root = elem->left;
    treeDestruct(tree);
    tree->root = elem->right;
    treeDestruct(tree);
    tree->root = elem;
    free(elem);
    tree->counter++;
    if (tree->counter == tree->number_of_nodes) {
        free(tree);
    }
}

//---------------------------------------
//! Prints the data of every node in sorted order
//! \param  [in]    tree    pointer to tree
//! \note the algorithm is recursive
//---------------------------------------

void printTree(binTree *tree) {
    ASSERT_OK(tree)
    node *elem = tree->root;
    if (!elem) return;
    tree->root = elem->left;
    printTree(tree);
    printf("%lf ", elem->data);
    tree->root = elem->right;
    printTree(tree);
    tree->root = elem;
    ASSERT_OK(tree)
}

//-----------------------------------------
//! Pushes the newNode to tree
//! \param  [in]    tree    pointer to tree
//! \param  [in]    newNode pointer to new node
//! \note the algorithm is recursive
//-----------------------------------------

void treePush(binTree *tree, node *newNode) {
    ASSERT_OK(tree)
    node *elem = tree->root;
    if (newNode->data <= elem->data) {
        if (elem->left == NULL) {
            elem->left = newNode;
            tree->number_of_nodes++;
        } else {
            tree->root = elem->left;
            treePush(tree, newNode);
        }
    } else {
        if (elem->right == NULL) {
            elem->right = newNode;
            tree->number_of_nodes++;
        } else {
            tree->root = elem->right;
            treePush(tree, newNode);
        }
    }
    tree->root = elem;
    ASSERT_OK(tree)
}

//-----------------------------------------
//! Pushes new node with data to tree
//! \param  [in]    tree    pointer to tree
//! \param  [in]    data    data of new node
//! \note the algorithm is recursive
//-----------------------------------------

void treePush(binTree *tree, double data) {
    ASSERT_OK(tree)
    node *elem = (node *) calloc(1, sizeof(node));
    elem->data = data;
    elem->left = NULL;
    elem->right = NULL;
    treePush(tree, elem);
}

//-------------------------------------------
//! Verificates the tree
//! \param  [in]    tree    pointer to tree
//! \return true, if tree is OK
//! \note the algorithm is recursive
//-------------------------------------------

bool treeOK(binTree *tree) {
    if (!(tree->root)) return true;
    if (tree) {
        node *elem = tree->root;
        tree->root = elem->left;
        treeOK(tree);
        tree->root = elem->right;
        treeOK(tree);
        tree->root = elem;
        tree->counter++;
    } else {
        return false;
    }
    return tree->counter == tree->number_of_nodes;
}

//--------------------------------------------
//! Makes the .dot file
//! \param  [in]    tree    pointer to tree
//--------------------------------------------

void treeDUMP(binTree *tree) {
    char *dump = (char *) calloc(MAX_GRAPH, sizeof(char));
    strncat(dump, "digraph {\n", MAX_GRAPH);
    collectTree(tree, dump);
    strncat(dump, "}", MAX_GRAPH);
    FILE *dotfile = fopen("tree.dot", "w");
    fwrite(dump, sizeof(char), MAX_GRAPH, dotfile);
    fclose(dotfile);
    system("dot -Tpng tree.dot -o tree.png");
    system("gwenview tree.png");
}

//-----------------------------------------------
//! Collects all the collections in tree
//! \param  [in]    tree    pointer to tree
//! \param  [in]    dump    string of .dot file
//! \note the algorithm is recursive
//-----------------------------------------------

void collectTree(binTree *tree, char *dump) {
    node *elem = tree->root;
    char *str = (char *) calloc(MAX_STR, sizeof(char));
    if (!elem) return;
    if (elem->left) {
        sprintf(str, "%.2lf", elem->data);
        strncat(dump, str, MAX_GRAPH);
        strncat(dump, "->", MAX_GRAPH);
        sprintf(str, "%.2lf", elem->left->data);
        strncat(dump, str, MAX_GRAPH);
        strncat(dump, "\n", MAX_GRAPH);
    }
    if (elem->right) {
        sprintf(str, "%.2lf", elem->data);
        strncat(dump, str, MAX_GRAPH);
        strncat(dump, "->", MAX_GRAPH);
        sprintf(str, "%.2lf", elem->right->data);
        strncat(dump, str, MAX_GRAPH);
        strncat(dump, "\n", MAX_GRAPH);
    }
    tree->root = elem->left;
    collectTree(tree, dump);
    tree->root = elem->right;
    collectTree(tree, dump);
    tree->root = elem;
}