#include <iostream>

#define ASSERT_OK() if (!stackOK(stack)) stack_DUMP(stack)
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

void stackConstruct(stack_t *stack, int size) {
    stack->count = 0;
    stack->size = size;
    stack->data = (stackElem_t *) malloc(stack->size * sizeof(stackElem_t));
    ASSERT_OK();
}

void stackDestruct(stack_t *stack) {
    free(stack->data);
    free(stack);
}

void stackPush(stack_t *stack, stackElem_t element) {
    ASSERT_OK();
    stack->data[stack->count++] = element;
    if (stack->count == stack->size) {
        stackResize(stack);
    }
    ASSERT_OK();
}

stackElem_t stackPop(stack_t *stack){
    ASSERT_OK();
    stackElem_t res = stack->data[stack->count-1];
    stack->data[(stack->count--)-1] = 0;
    ASSERT_OK();
    return res;
}

bool stackOK(stack_t *stack) {
    return stack && stack->count >= 0 && stack->size > 0 && stack->data;
}

void stack_DUMP(stack_t *stack) {
    if (stackOK(stack)) {
        printf("stack_t [%#010x] \n{\t", stack);
        printf("size = %d\n\t", stack->size);
        printf("data [%d][%#010x] = {\n\t\t", stack->count, stack->data);
        for (int i = 0; i < stack->count; i++) {
            printf("[%d] = %lf\n\t\t", i, stack->data[i]); //TODO: MAKE IT FOR STACK_ELEM_T
        }
        printf("}\n");
    } else {
        if (stack) {
            printf("stack_t [%#010x] (ERROR!!!)\n{\t", stack);
            if (stack->size > 0) {
                printf("size = %d\n\t", stack->size);
                if (stack->count >= 0){
                    printf("data [%d][%s%#010x%s] = {}\n", stack->count, RED, stack->data, RESET);
                } else {
                    printf("data [%s%d%s][%#010x] = {}\n", RED, stack->count, RESET, stack->data);
                }
            } else {
                printf("%ssize = %d%s\n", RED, stack->size, RESET);
            }
        } else {
            printf("stack_t [%s%#010x%s] (ERROR!!!)\n{", RED, stack, RESET);
        }
    }
    printf("}");
}

void stackResize(stack_t *stack) {
    stack->size *= 2;
    realloc(stack->data, stack->size * sizeof(stackElem_t));
}