#include <iostream>
#include "differentiator.h"

int main() {
    binTree *diffTree = NULL;
    diffTree = treeConstruct(diffTree);
    diffTree = makeTree(diffTree);
    d(diffTree->root);
    optimizer(diffTree->root);
    printResult(diffTree);
    treeDestruct(diffTree);
    return 0;
}