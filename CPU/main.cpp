#include <iostream>
#include <tgmath.h>
#include <fcntl.h>
#include <zconf.h>
#include "stack.h"
#include "rfile.h"

#define FILE_OPEN_READ(fp) if (!fp) {perror("open"); exit(-1);}

enum cmd {
    PUSH = 1,
    MUL,
    SUB,
    SQRT,
    ADD,
    DIV,
    SIN,
    COS,
    OUT,
    PUSH_X,
    AX = 51,
    BX,
    CX,
    DX,
    POP = 20,
    JMP = 60,
    JE,
    JNE,
    JAE,
    JA,
    JB,
    JBE,
    CALL = 70,
    RET,
    END = 100
};

struct CPU {
    int cmd_pointer = 0;
    stack_t *data_stack = NULL;
    stack_t *return_stack = NULL;
};

const char *computer_code = "comp";
const double POISON = atan(M_PI / 2);

void file_to_array(int *, FILE *);

void run_the_executor(CPU *, int *);

CPU *cpuConstruct(CPU *);

void cpuDestruct(CPU *);

int main() {
    CPU *cpu = NULL;
    cpu = cpuConstruct(cpu);

    errno = 0;
    FILE *script = fopen(computer_code, "rb");
    FILE_OPEN_READ(script)
    int *code = (int *) calloc(get_file_size(script), sizeof(int));
    assert(code);
    file_to_array(code, script);
    fclose(script);

    run_the_executor(cpu, code);

    cpuDestruct(cpu);
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
    do {
        fread(&command, 1, 1, script);
        code[count] = command;
        count += 1;
        if (command == PUSH || command == PUSH_X || command == POP || (command >= JMP && command <= JBE) ||
            command == CALL) {
            fread(&command, 4, 1, script);
            code[count] = command;
            count += 1;
        }
    } while (command != END);
}

//------------------------------
//! Executes the asm script
//!
//! \param  cpu   pointer to stack
//! \param  code    pointer to computer code
//!
//! \return result of execution the script
//------------------------------

void run_the_executor(CPU *cpu, int *code) {
    assert(cpu);
    assert(code);
    double ax = POISON, bx = POISON, cx = POISON, dx = POISON;
    while (code[cpu->cmd_pointer] != END) {
        switch (code[cpu->cmd_pointer]) {
            case PUSH:
                stackPush(cpu->data_stack, code[cpu->cmd_pointer + 1]);
                cpu->cmd_pointer += 2;
                break;
            case PUSH_X:
                switch (code[cpu->cmd_pointer + 1]) {
                    case AX:
                        assert(ax != POISON);
                        assert(std::isfinite(ax));
                        stackPush(cpu->data_stack, ax);
                        break;
                    case BX:
                        assert(bx != POISON);
                        assert(std::isfinite(bx));
                        stackPush(cpu->data_stack, bx);
                        break;
                    case CX:
                        assert(cx != POISON);
                        assert(std::isfinite(cx));
                        stackPush(cpu->data_stack, cx);
                        break;
                    case DX:
                        assert(dx != POISON);
                        assert(std::isfinite(dx));
                        stackPush(cpu->data_stack, dx);
                        break;
                    default:
                        printf("SOMETHING WENT WRONG! No such register %d", code[cpu->cmd_pointer + 1]);
                        assert(0);
                }
                cpu->cmd_pointer += 2;
                break;
            case JMP:
                cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case JE:
                if (stackPop(cpu->data_stack) == stackPop(cpu->data_stack))
                    cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case JNE:
                if (stackPop(cpu->data_stack) != stackPop(cpu->data_stack))
                    cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case JAE:
                if (stackPop(cpu->data_stack) <= stackPop(cpu->data_stack))
                    cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case JA:
                if (stackPop(cpu->data_stack) < stackPop(cpu->data_stack))
                    cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case JB:
                if (stackPop(cpu->data_stack) > stackPop(cpu->data_stack))
                    cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case JBE:
                if (stackPop(cpu->data_stack) >= stackPop(cpu->data_stack))
                    cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case CALL:
                stackPush(cpu->return_stack, cpu->cmd_pointer + 2);
                cpu->cmd_pointer = code[cpu->cmd_pointer + 1];
                break;
            case RET:
                cpu->cmd_pointer = (int) stackPop(cpu->return_stack);
                break;
            case POP:
                switch (code[cpu->cmd_pointer + 1]) {
                    case AX:
                        ax = stackPop(cpu->data_stack);
                        break;
                    case BX:
                        bx = stackPop(cpu->data_stack);
                        break;
                    case CX:
                        cx = stackPop(cpu->data_stack);
                        break;
                    case DX:
                        dx = stackPop(cpu->data_stack);
                        break;
                    default:
                        printf("SOMETHING WENT WRONG! No such register %d", code[cpu->cmd_pointer + 1]);
                        assert(0);
                }
                cpu->cmd_pointer += 2;
                break;
            case MUL:
                stackPush(cpu->data_stack, stackPop(cpu->data_stack) * stackPop(cpu->data_stack));
                cpu->cmd_pointer += 1;
                break;
            case SUB:
                stackPush(cpu->data_stack, -(stackPop(cpu->data_stack) - stackPop(cpu->data_stack)));
                cpu->cmd_pointer += 1;
                break;
            case SQRT:
                stackPush(cpu->data_stack, sqrt(stackPop(cpu->data_stack)));
                cpu->cmd_pointer += 1;
                break;
            case ADD:
                stackPush(cpu->data_stack, stackPop(cpu->data_stack) + stackPop(cpu->data_stack));
                cpu->cmd_pointer += 1;
                break;
            case DIV:
                stackPush(cpu->data_stack, 1.0 / stackPop(cpu->data_stack) * stackPop(cpu->data_stack));
                cpu->cmd_pointer += 1;
                break;
            case SIN:
                stackPush(cpu->data_stack, sin(stackPop(cpu->data_stack)));
                cpu->cmd_pointer += 1;
                break;
            case COS:
                stackPush(cpu->data_stack, cos(stackPop(cpu->data_stack)));
                cpu->cmd_pointer += 1;
                break;
            case OUT:
                printf("%lf", stackPop(cpu->data_stack));
                cpu->cmd_pointer += 1;
                break;
            default:
                printf("SOMETHING WENT WRONG! The command is %d", code[cpu->cmd_pointer]);
                assert(0);
        }
    }
}

//------------------------------
//! Initializing the CPU
//!
//! \param cpu    pointer to CPU
//!
//! \return initialized cpu
//------------------------------

CPU *cpuConstruct(CPU *cpu) {
    cpu = (CPU *) calloc(1, sizeof(CPU));
    assert(cpu);
    cpu->data_stack = stackConstruct(cpu->data_stack, 10);
    cpu->return_stack = stackConstruct(cpu->return_stack, 10);
    return cpu;
}

//------------------------------
//! Free the memory of the cpu
//!
//! \param cpu    pointer to cpu
//!
//! \return memory of the computer
//------------------------------

void cpuDestruct(CPU *cpu) {
    stackDestruct(cpu->data_stack);
    stackDestruct(cpu->return_stack);
    free(cpu);
}