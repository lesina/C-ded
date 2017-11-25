#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include "binary_tree.h"
#include "differentiator.h"

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

binTree *treeConstruct(binTree *tree, nodeType data) {
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

node *nodeConstruct(node *elem, nodeType data) {
    elem = (node *) calloc(1, sizeof(node));
    assert(elem);
    elem->data = data;
    elem->left = NULL;
    elem->right = NULL;
    if (!strcmp(data, "x")) {
        elem->type = VARIABLE;
    } else if (!strcmp(data, "+") || !strcmp(data, "*") || !strcmp(data, "-")) {
        elem->type = OPERATOR;
    } else {
        elem->type = NUMBER;
    }
    return elem;
}

//-----------------------------------------
//! Free the memory of every node and tree
//! \param  [in]    tree    pointer to tree
//! \note the algorithm is recursive
//-----------------------------------------

void treeDestruct(binTree *tree) {
    node *elem = tree->root;
    if (!elem) return;
    tree->root = elem->left;
    treeDestruct(tree);
    tree->root = elem->right;
    treeDestruct(tree);
    tree->root = elem;
    free(elem);
    tree->counter++;
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
    printf("%s ", elem->data);
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
    assert(tree);
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
}

//-----------------------------------------
//! Pushes new node with data to tree
//! \param  [in]    tree    pointer to tree
//! \param  [in]    data    data of new node
//! \note the algorithm is recursive
//-----------------------------------------

void treePush(binTree *tree, nodeType data) {
    ASSERT_OK(tree)
    node *elem = nodeConstruct(elem, data);
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

//-----------------------------------------
//! Makes tree from tree file
//! \param  [in]    tree    pointer to tree
//! \return resulted tree
//-----------------------------------------

binTree *makeTree(binTree *tree) {
    char *str = (char *) calloc(MAX_LEN, sizeof(char));
    assert(str);

    errno = 0;
    FILE *file = fopen("tree", "r");
    ASSERT_FILE(file)

    fscanf(file, "{ %s {", str);
    tree = treeConstruct(tree, str);

    collectTree(tree, file);

    fclose(file);
    return tree;
}

//--------------------------------------------
//! Collects all the information from tree file
//! \param  [in]    tree    pointer to tree
//! \param  [in]    file    pointer to tree file
//--------------------------------------------

void collectTree(binTree *tree, FILE *file) {
    char *str = (char *) calloc(MAX_LEN, sizeof(char));
    assert(str);
    char *word = (char *) calloc(MAX_LEN, sizeof(char));
    assert(word);

    node *elem = tree->root;

    fscanf(file, "%s", word);
    while (strcmp(word, "{") && strcmp(word, ",")) {
        strncat(str, word, MAX_LEN);
//        strncat(str, "_", MAX_LEN);
        fscanf(file, "%s", word);
    }
    if (!strcmp(str, "NULL")) {
        tree->root->left = NULL;
    } else {
        tree->root->left = nodeConstruct(tree->root->left, str);
    }

    if (!strcmp(word, "{")) {
        tree->root = tree->root->left;
        collectTree(tree, file);
        tree->root = elem;
        fscanf(file, "%s", word);
    }

    if (!strcmp(word, ",")) {
        str = (char *) calloc(MAX_LEN, sizeof(char));
        fscanf(file, "%s", word);
        while (strcmp(word, "{") && strcmp(word, "}")) {
            strncat(str, word, MAX_LEN);
//            strncat(str, "_", MAX_LEN);
            fscanf(file, "%s", word);
        }

        if (!strcmp(str, "NULL")) {
            tree->root->right = NULL;
        } else {
            tree->root->right = nodeConstruct(tree->root->right, str);
        }
    }

    if (!strcmp(word, "{")) {
        tree->root = tree->root->right;
        collectTree(tree, file);
        tree->root = elem;
        fscanf(file, "%s", word);
    }
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
    assert(str);
    if (!elem) return;
    if (elem->left) {
//        sprintf(str, "%.2lf", elem->data);
        strncat(dump, elem->data, MAX_GRAPH);
        strncat(dump, "->", MAX_GRAPH);
//        sprintf(str, "%.2lf", elem->left->data);
        strncat(dump, elem->left->data, MAX_GRAPH);
        strncat(dump, "\n", MAX_GRAPH);
    }
    if (elem->right) {
//        sprintf(str, "%.2lf", elem->data);
        strncat(dump, elem->data, MAX_GRAPH);
        strncat(dump, "->", MAX_GRAPH);
//        sprintf(str, "%.2lf", elem->right->data);
        strncat(dump, elem->right->data, MAX_GRAPH);
        strncat(dump, "\n", MAX_GRAPH);
    }
    tree->root = elem->left;
    collectTree(tree, dump);
    tree->root = elem->right;
    collectTree(tree, dump);
    tree->root = elem;
}