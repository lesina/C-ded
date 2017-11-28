#include "differentiator.h"

int main() {
    binTree *diffTree = NULL;
    diffTree = treeConstruct(diffTree);
    diffTree = makeTree(diffTree);
    printResult(diffTree);
    printf("\n");
    d(diffTree->root);
    optimizer(diffTree->root);
    printResult(diffTree);
    treeDestruct(diffTree);
    return 0;
}