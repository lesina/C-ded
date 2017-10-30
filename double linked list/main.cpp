#include <iostream>
#include "dllist.h"

int main() {
    list_t *list = NULL;
    list = listConstruct(list);

    listPush(list, 5);
    listPush(list, 10);

    listDestruct(list);
    return 0;
}