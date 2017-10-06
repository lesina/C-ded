#include <iostream>

#define RED     "\033[1;31m"
#define RESET   "\033[0m"

typedef double stackElem_t;
struct stack_t {
    stackElem_t *data;
    int count;
};

void stackConstruct(stack_t *stack);

void stackDestruct(stack_t *stack);

//void stackPush(stack_t *stack, stackElem_t element);

//void stackPop(stack_t *stack);

bool stackOK(stack_t *stack);

void stack_DUMP(stack_t *stack);

int main() {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stackConstruct(stack);
    stack_DUMP(stack);
    stackDestruct(stack);
    return 0;
}

void stackConstruct(stack_t *stack) {
    stack->count = 10;
    stack->data = (stackElem_t *) malloc(stack->count * sizeof(stackElem_t));
}

void stackDestruct(stack_t *stack) {
    free(stack->data);
    free(stack);
}

//void stackPush(stack_t *stack, stackElem_t element)

//void stackPop(stack_t *stack)

bool stackOK(stack_t *stack) {
    return stack && stack->count > 0 && stack->data;
}

void stack_DUMP(stack_t *stack) {
    if (stackOK(stack)) {
        printf("stack_t [%d] \n{\t", stack);
    } else {
        printf("stack_t [%d] (ERROR!!!)\n{\t", stack);
    }
    if (stack->count <= 0) {
        printf("%s count = %d %s\n\t", RED, stack->count, RESET);
    } else {
        printf("count = %d\n\t", stack->count);
    }
    printf("}");
}