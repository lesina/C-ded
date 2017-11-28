#include <iostream>
#include "reccirc.h"

#define FILE_ERROR_OPEN(file) if (!file) { perror("open"); exit(-1); }

int main() {

    errno = 0;
    FILE *file = fopen("expression", "r");
    FILE_ERROR_OPEN(file);

    calculate(file);

    return 0;
}