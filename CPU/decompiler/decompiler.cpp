#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include "rfile.h"

#define FD_ERROR_OPEN(fd) if (fd == -1) { perror("open"); exit(-1); }
#define PUSH "1"
#define MUL "2"
#define SUB "3"
#define SQRT "4"
#define ADD "5"
#define DIV "6"
#define SIN "7"
#define COS "8"
#define OUT "9"
#define END "100"
#define PUSH_X "10"
#define POP "20"
#define AX "51"
#define BX "52"
#define CX "53"
#define DX "54"

const char *asm_script = "asm_script";
const int MAX_N_TAGS = 65536;

void write_to_file(char *);

void collect_tags(int *, char *);

int main() {
    printf("Please, enter the name of computer code file: ");
    char *file_script = (char *) malloc(FILENAME_MAX);
    scanf("%s", file_script);

    errno = 0;
    int fd_read = open(file_script, O_RDONLY);
    FD_ERROR_OPEN(fd_read);

    long int size_of_file = get_file_size(fd_read);

    char buf[size_of_file];

    //TODO: FINISH THE WORK WITH TAGS AND TAG-FUNCTION
    read(fd_read, buf, size_of_file);
//    int *tags = (int *) calloc(MAX_N_TAGS, sizeof(int));
//    collect_tags(tags, buf);

    read(fd_read, buf, size_of_file);
    write_to_file(buf);

    close(fd_read);

    return 0;
}

//-------------------------------------------
//! Writing script in computer code
//!
//! @param  [in]    buf     the whole script
//!
//! @return File with understandable code
//-------------------------------------------

void write_to_file(char *buf) {
    assert(buf);
    int fd_write = open(asm_script, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FD_ERROR_OPEN(fd_write);

    char *pch = strtok(buf, " \n@");
    while (pch != NULL) {
        if (!strcmp(pch, PUSH)) {
            write(fd_write, "push ", 5);
            pch = strtok(NULL, " \n@");
            write(fd_write, pch, strlen(pch));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, PUSH_X)) {
            write(fd_write, "push ", 5);
            pch = strtok(NULL, " \n@");
            if (!strcmp(pch, AX)) {
                write(fd_write, "ax", 2);
            } else if (!strcmp(pch, BX)) {
                write(fd_write, "bx", 2);
            } else if (!strcmp(pch, CX)) {
                write(fd_write, "cx", 2);
            } else if (!strcmp(pch, DX)) {
                write(fd_write, "dx", 2);
            }
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, POP)) {
            write(fd_write, "pop ", 4);
            pch = strtok(NULL, " \n@");
            if (!strcmp(pch, AX)) {
                write(fd_write, "ax", 2);
            } else if (!strcmp(pch, BX)) {
                write(fd_write, "bx", 2);
            } else if (!strcmp(pch, CX)) {
                write(fd_write, "cx", 2);
            } else if (!strcmp(pch, DX)) {
                write(fd_write, "dx", 2);
            }
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, MUL)) {
            write(fd_write, "mul", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, SUB)) {
            write(fd_write, "sub", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, SQRT)) {
            write(fd_write, "sqrt", 4);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, ADD)) {
            write(fd_write, "add", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, DIV)) {
            write(fd_write, "div", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, SIN)) {
            write(fd_write, "sin", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, COS)) {
            write(fd_write, "cos", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, OUT)) {
            write(fd_write, "out", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, END)) {
            write(fd_write, "end", 3);
            write(fd_write, "\n", 1);
        }
        pch = strtok(NULL, " \n@");
    }
    close(fd_write);
}

//-------------------------------------------
//! Collecting tags
//!
//! @param  [in]    tags    array of tags
//! @param  [in]    buf     the whole script
//!
//! @return Array of tags destination
//-------------------------------------------

void collect_tags(int *tags, char *buf) {
    assert(buf);
    assert(tags);
}