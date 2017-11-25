#ifndef DIFFERENTIATOR_DIFFERENTIATOR_H
#define DIFFERENTIATOR_DIFFERENTIATOR_H

#include "binary_tree.h"

enum types {
    NUMBER = 1,
    VARIABLE,
    OPERATOR
};

void d(node *);

void createNode(node *, nodeType, int);

void createNodeMul(node *, nodeType, node *, node *, int);

node *copy(node *);

node *difficultFunc(node *, node *(*)(node *));

node *diffSin(node *);

node *diffCos(node *);

void printResult(binTree *);

void optimizer(node *);

void calculateConst(node *, int *);

void calculate(node *, int *);

#endif //DIFFERENTIATOR_DIFFERENTIATOR_H
