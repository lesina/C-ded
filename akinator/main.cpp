#include <iostream>
#include <cstring>
#include <cassert>
#include "binary_tree.h"
#include "akinator.h"

int main() {
    binTree *tree = NULL;
    tree = makeTree(tree);

    while (true) {
        char *answer = (char *) calloc(MAX_LEN, sizeof(char));
        assert(answer);
        game(tree);
        printf("Play again? (yes/no) ");
        scanf("%s", answer);
        if (!strcmp(answer, "no")) {
            break;
        }
    }

    treeDUMP(tree);
    treeDestruct(tree);
    return 0;
}