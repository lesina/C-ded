#include <iostream>
#include "stack.h"

int main() {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stackConstruct(stack, 10);
    stackPush(stack, 5);
    printf("%lf\n", stackPop(stack));
    printf("%d\n", stack->count);
    printf("%d", stack->size);
    stackDestruct(stack);
    return 0;
}