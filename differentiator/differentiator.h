#ifndef DIFFERENTIATOR_DIFFERENTIATOR_H
#define DIFFERENTIATOR_DIFFERENTIATOR_H

#include "binary_tree.h"

enum types {
    NUMBER = 1,
    VARIABLE,
    OPERATOR
};

void d(node *);

void createNode(node*, nodeType);

void createNode(node*, nodeType, node *);

void createNode(node*, nodeType, node *, node *);

node *copy(node *);

node *difficultFunc(node *, node *);

node *diffSin(node *);

node *diffCos(node *);

void printResult(binTree *);

#endif //DIFFERENTIATOR_DIFFERENTIATOR_H
