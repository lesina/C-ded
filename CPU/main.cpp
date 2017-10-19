#include <iostream>
#include <tgmath.h>
#include "stack.h"
#include "rfile.h"

#define PUSH 1
#define MUL 2
#define SUB 3
#define SQRT 4
#define ADD 5
#define DIV 6
#define SIN 7
#define COS 8
#define OUT 9
#define END 100
#define PUSH_X 10
#define AX 51
#define BX 52
#define CX 53
#define DX 54
#define POP 20
#define JMP 60
#define JE 61
#define JNE 62
#define JAE 63
#define JA 64
#define JB 65
#define JBE 66
#define CALL 70
#define RET 71

const char *computer_code = "comp";
const double POISON = atan(M_PI / 2);

void file_to_array(int *, FILE *);

void run_the_executor(stack_t *, int *);

int main() {
    stack_t *stack = (stack_t *) malloc(sizeof(stack_t));
    stackConstruct(stack, 10);

    FILE *script = fopen(computer_code, "r");
    int *code = (int *) calloc(get_file_size(script), sizeof(int));
    file_to_array(code, script);
    fclose(script);

    run_the_executor(stack, code);

    stackDestruct(stack);
    return 0;
}

//------------------------------
//! Puts code from file into array
//!
//! \param  code    pointer to computer code
//! \param  script  file pointer to code
//!
//! \return array of code
//------------------------------

void file_to_array(int *code, FILE *script) {
    assert(script);
    assert(code);
    int count = 0;
    int command = 0;
    fscanf(script, "%d", &command);
    while (command != END) {
        code[count] = command;
        count += 1;
        fscanf(script, "%d", &command);
    }
    code[count] = command;
}

//------------------------------
//! Executes the asm script
//!
//! \param  stack   pointer to stack
//! \param  code    pointer to computer code
//!
//! \return result of execution the script
//------------------------------

void run_the_executor(stack_t *stack, int *code) {
    assert(stack);
    assert(code);
    stack_t *ret = (stack_t *) malloc(sizeof(stack_t));
    stackConstruct(stack, 10);
    double ax = POISON, bx = POISON, cx = POISON, dx = POISON;
    int cmdCount = 0;
    while (code[cmdCount] != END) {
        switch (code[cmdCount]) {
            case PUSH:
                stackPush(stack, code[cmdCount + 1]);
                cmdCount += 2;
                break;
            case PUSH_X:
                switch (code[cmdCount + 1]) {
                    case AX:
                        assert(ax != POISON);
                        assert(std::isfinite(ax));
                        stackPush(stack, ax);
                        break;
                    case BX:
                        assert(bx != POISON);
                        assert(std::isfinite(bx));
                        stackPush(stack, bx);
                        break;
                    case CX:
                        assert(cx != POISON);
                        assert(std::isfinite(cx));
                        stackPush(stack, cx);
                        break;
                    case DX:
                        assert(dx != POISON);
                        assert(std::isfinite(dx));
                        stackPush(stack, dx);
                        break;
                    default:
                        printf("SOMETHING WENT WRONG! No such register %d", code[cmdCount + 1]);
                        assert(0);
                }
                cmdCount += 2;
                break;
            case JMP:
                cmdCount = code[cmdCount + 1];
                break;
            case JE:
                if (stackPop(stack) == stackPop(stack)) cmdCount = code[cmdCount + 1];
                break;
            case JNE:
                if (stackPop(stack) == stackPop(stack)) cmdCount = code[cmdCount + 1];
                break;
            case JAE:
                if (stackPop(stack) <= stackPop(stack)) cmdCount = code[cmdCount + 1];
                break;
            case JA:
                if (stackPop(stack) < stackPop(stack)) cmdCount = code[cmdCount + 1];
                break;
            case JB:
                if (stackPop(stack) > stackPop(stack)) cmdCount = code[cmdCount + 1];
                break;
            case JBE:
                if (stackPop(stack) >= stackPop(stack)) cmdCount = code[cmdCount + 1];
                break;
            case CALL:
                stackPush(ret, cmdCount + 2);
                cmdCount = code[cmdCount + 1];
                break;
            case RET:
                cmdCount = (int) stackPop(ret);
                break;
            case POP:
                switch (code[cmdCount + 1]) {
                    case AX:
                        ax = stackPop(stack);
                        break;
                    case BX:
                        bx = stackPop(stack);
                        break;
                    case CX:
                        cx = stackPop(stack);
                        break;
                    case DX:
                        dx = stackPop(stack);
                        break;
                    default:
                        printf("SOMETHING WENT WRONG! No such register %d", code[cmdCount + 1]);
                        assert(0);
                }
                cmdCount += 2;
                break;
            case MUL:
                stackPush(stack, stackPop(stack) * stackPop(stack));
                cmdCount += 1;
                break;
            case SUB:
                stackPush(stack, -(stackPop(stack) - stackPop(stack)));
                cmdCount += 1;
                break;
            case SQRT:
                stackPush(stack, sqrt(stackPop(stack)));
                cmdCount += 1;
                break;
            case ADD:
                stackPush(stack, stackPop(stack) + stackPop(stack));
                cmdCount += 1;
                break;
            case DIV:
                stackPush(stack, 1.0 / stackPop(stack) * stackPop(stack));
                cmdCount += 1;
                break;
            case SIN:
                stackPush(stack, sin(stackPop(stack)));
                cmdCount += 1;
                break;
            case COS:
                stackPush(stack, cos(stackPop(stack)));
                cmdCount += 1;
                break;
            case OUT:
                printf("%lf", stackPop(stack));
                cmdCount += 1;
                break;
            default:
                printf("SOMETHING WENT WRONG! The command is %d", code[cmdCount]);
                assert(0);
        }
    }
    stackDestruct(stack);
}