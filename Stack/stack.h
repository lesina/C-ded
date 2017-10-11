#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <cassert>
#include <iostream>

#define ASSERT_OK() if (!stackOK(stack)) {stack_DUMP(stack); assert(0);}
#define RED     "\033[1;31m"
#define RESET   "\033[0m"

typedef double stackElem_t;
struct stack_t {
    stackElem_t *data;
    int count;
    int size;
};

void stackConstruct(stack_t *stack, int size);

void stackDestruct(stack_t *stack);

void stackPush(stack_t *stack, stackElem_t element);

stackElem_t stackPop(stack_t *stack);

bool stackOK(stack_t *stack);

void stack_DUMP(stack_t *stack);

void stackResize(stack_t *stack);


#endif //STACK_STACK_H
