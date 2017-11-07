#ifndef AKINATOR_AKINATOR_H
#define AKINATOR_AKINATOR_H

#define ASSERT_FILE(file) if (!file) { perror("open"); exit(-1); }

#include "binary_tree.h"

const int MAX_LEN = 255;

binTree *makeTree(binTree *);

void collectTree(binTree *, FILE *);

void game(binTree *);

#endif //AKINATOR_AKINATOR_H
