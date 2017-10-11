#include <iostream>
#include <tgmath.h>
#include "stack.h"

const char *computer_commands = "comp";
const double POISON = atan(M_PI / 2);

void run_the_executor(stack_t *);

int main() {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stackConstruct(stack, 10);

    run_the_executor(stack);

    stackDestruct(stack);
    return 0;
}

//------------------------------
//! Executes the asm script
//!
//! \param stack    pointer to stack
//!
//! \return result of execution the script
//------------------------------

void run_the_executor(stack_t *stack) {
    assert(stack);
    FILE *script = fopen(computer_commands, "r");
    assert(script);
    int command = 0;
    double value = POISON;
    fscanf(script, "%d", &command);
    while (command != -1) {
        switch (command) {
            case 1:
                fscanf(script, "%lf", &value);
                assert(value != POISON);
                assert(std::isfinite(value));
                stackPush(stack, value);
                break;
            case 2:
                stackPush(stack, stackPop(stack) * stackPop(stack));
                break;
            case 3:
                stackPush(stack, -(stackPop(stack) - stackPop(stack)));
                break;
            case 4:
                stackPush(stack, sqrt(stackPop(stack)));
                break;
            case 5:
                stackPush(stack, stackPop(stack) + stackPop(stack));
                break;
            case 6:
                stackPush(stack, 1.0 / stackPop(stack) * stackPop(stack));
                break;
            case 7:
                stackPush(stack, sin(stackPop(stack)));
                break;
            case 8:
                stackPush(stack, cos(stackPop(stack)));
                break;
            case 9:
                printf("%lf", stackPop(stack));
                break;
            default:
                printf("No command %d in this version of asm\n", command);
                assert(0);
        }
        fscanf(script, "%d", &command);
    }
}