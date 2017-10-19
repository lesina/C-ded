#include "stack.h"

//------------------------------
//! Initializing the stack
//!
//! \param stack    pointer to stack
//! \param size     size of data-array
//!
//! \return initialized stack
//!
//! \note count - number of the next element, size - size of memory allocated to stack
//------------------------------

void stackConstruct(stack_t *stack, int size = 1) {
    stack->count = 0;
    stack->size = size;
    stack->data = (stackElem_t *) malloc(stack->size * sizeof(stackElem_t));
    ASSERT_OK()
}

//------------------------------
//! Free the memory of the stack
//!
//! \param stack    pointer to stack
//!
//! \return memory of the computer
//------------------------------

void stackDestruct(stack_t *stack) {
    ASSERT_OK()
    free(stack->data);
    free(stack);
}

//------------------------------
//! Pushes the element to the end of stack data
//!
//! \param stack    pointer to stack
//! \param element  element which is pushed to the top of stack
//!
//! \return updated stack
//------------------------------

void stackPush(stack_t *stack, stackElem_t element) {
    ASSERT_OK()
    stack->data[stack->count++] = element;
    if (stack->count == stack->size) {
        stackResize(stack);
    }
    ASSERT_OK()
}

//------------------------------
//! Pops the element from the end of stack data
//!
//! \param stack    pointer to stack
//!
//! \return popped element
//!
//! \note can't pop the element from stack with count = 0 or less
//------------------------------

stackElem_t stackPop(stack_t *stack) {
    ASSERT_OK()
    assert(stack->count > 0);
    stackElem_t res = stack->data[stack->count - 1];
    stack->data[(stack->count--) - 1] = 0;
    ASSERT_OK()
    return res;
}

//------------------------------
//! Checks if the stack is OK
//!
//! \param stack    pointer to stack
//!
//! \return true, if everything is good; false - if not
//------------------------------

bool stackOK(stack_t *stack) {
    return stack && stack->count >= 0 && stack->size > 0 && stack->data;
}

//------------------------------
//! Prints the dump of stack
//!
//! \param stack    pointer to stack
//!
//! \return dump of stack
//------------------------------

void stack_DUMP(stack_t *stack) {
    ASSERT_OK()
    if (stackOK(stack)) {
        printf("stack_t [%#010x] \n{\t", stack);
        printf("size = %d\n\t", stack->size);
        printf("data [%d][%#010x] = {\n\t\t", stack->count, stack->data);
        for (int i = 0; i < stack->count; i++) {
            printf("[%d] = %lf\n\t\t", i, stack->data[i]);
        }
        printf("}\n");
    } else {
        if (stack) {
            printf("stack_t [%#010x] (ERROR!!!)\n{\t", stack);
            if (stack->size > 0) {
                printf("size = %d\n\t", stack->size);
                if (stack->count >= 0) {
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

//------------------------------
//! Resizes the stack
//!
//! \param stack    pointer to stack
//!
//! \return Updated stack
//------------------------------

void stackResize(stack_t *stack) {
    ASSERT_OK()
    stack->size *= 2;
    stack->data = (stackElem_t *) realloc(stack->data, stack->size * sizeof(stackElem_t));
    ASSERT_OK()
}