#ifndef AKINATOR_BINARY_TREE_H
#define AKINATOR_BINARY_TREE_H

#define ASSERT_OK(tree) if (!treeOK(tree)) { tree->counter = 0; treeDUMP(tree); exit(-1); } else {tree->counter = 0;}

const int MAX_STR = 20;
const int MAX_GRAPH = 40000;

typedef char* nodeType;
struct node {
    nodeType data;
    node *left, *right;
};

struct binTree {
    node *root;
    int number_of_nodes;
    int counter;
};

binTree *treeConstruct(binTree *);

binTree *treeConstruct(binTree *, nodeType);

binTree *treeConstruct(binTree *, node *);

node *nodeConstruct(node *, nodeType);

void treeDestruct(binTree *);

void printTree(binTree *);

void treePush(binTree *, nodeType);

void treePush(binTree *, node *);

bool treeOK(binTree *);

void treeDUMP(binTree *);

void collectTree(binTree *, char *);

#endif //AKINATOR_BINARY_TREE_H
