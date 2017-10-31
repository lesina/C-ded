#include <iostream>
#include "binary_tree.h"

int main() {
    binTree *tree = NULL;
    tree = treeConstruct(tree, 5);

    treePush(tree, 1);
    treePush(tree, 3);
    treePush(tree, 2);
    treePush(tree, 4);
    treePush(tree, 7);
    treePush(tree, 8);
    treePush(tree, 9);
    treePush(tree, 6);

    treeDUMP(tree);
    treeDestruct(tree);
    return 0;
}