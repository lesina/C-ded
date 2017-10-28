#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include "rfile.h"

#define FD_ERROR_OPEN(fd) if (fd == -1) { perror("open"); exit(-1); }
#define CMD_DEF(name, num) else if (!strcmp(pch, #name)) { x = num; write(fd_write, &x, 1); }
#define JMP_DEF(name, num) else if (!strcmp(pch, #name)) { x = num; write(fd_write, &x, 1); pch = strtok(NULL, " \n@");\
if (!tags[atoi(pch + 1)]) {printf("Tag %d is not existed\n", atoi(pch + 1));exit(-1);}write(fd_write, &tags[atoi(pch + 1)], 4);}

const char *computer_commands = "comp";
const int MAX_TAG = 2147483647;

void write_to_file(int *, char *);

void collect_tags(int *, char *);

int main() {
    printf("Please, enter the name of asm script: ");
    char *file_script = (char *) calloc(FILENAME_MAX, 1);
    assert(file_script);
    scanf("%s", file_script);

    errno = 0;
    int fd_read = open(file_script, O_RDONLY);
    FD_ERROR_OPEN(fd_read);

    long int size_of_file = get_file_size(fd_read);

    char *buf = (char *) calloc(size_of_file, sizeof(char));
    assert(buf);

    read(fd_read, buf, size_of_file);
    close(fd_read);
    int *tags = (int *) calloc(MAX_TAG, sizeof(int));
    assert(tags);
    collect_tags(tags, buf);

    fd_read = open(file_script, O_RDONLY);
    FD_ERROR_OPEN(fd_read);

    read(fd_read, buf, size_of_file);
    close(fd_read);
    write_to_file(tags, buf);

    return 0;
}

//-------------------------------------------
//! Writing script in computer code
//!
//! @param  [in]    buf     the whole script
//!
//! @return File with understandable code
//-------------------------------------------

void write_to_file(int *tags, char *buf) {
    int fd_write = open(computer_commands, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FD_ERROR_OPEN(fd_write);

    char *tag = (char *) calloc(5, sizeof(char));
    assert(tag);
    int x;
    bool has_no_end = true;
    char *pch = strtok(buf, " \n@");
    while (pch != NULL) {
        if (!strcmp(pch, "push")) {
            pch = strtok(NULL, " \n@");
            if (!strcmp(pch, "ax")) {
                x = 10;
                write(fd_write, &x, 1);
                x = 51;
                write(fd_write, &x, 4);
            } else if (!strcmp(pch, "bx")) {
                x = 10;
                write(fd_write, &x, 1);
                x = 52;
                write(fd_write, &x, 4);
            } else if (!strcmp(pch, "cx")) {
                x = 10;
                write(fd_write, &x, 1);
                x = 53;
                write(fd_write, &x, 4);
            } else if (!strcmp(pch, "dx")) {
                x = 10;
                write(fd_write, &x, 1);
                x = 54;
                write(fd_write, &x, 4);
            } else {
                x = 1;
                write(fd_write, &x, 1);
                x = atoi(pch);
                write(fd_write, &x, 4);
            }
        } else if (!strcmp(pch, "pop")) {
            x = 20;
            write(fd_write, &x, 1);
            pch = strtok(NULL, " \n@");
            if (!strcmp(pch, "ax")) {
                x = 51;
                write(fd_write, &x, 4);
            } else if (!strcmp(pch, "bx")) {
                x = 52;
                write(fd_write, &x, 4);
            } else if (!strcmp(pch, "cx")) {
                x = 53;
                write(fd_write, &x, 4);
            } else if (!strcmp(pch, "dx")) {
                x = 54;
                write(fd_write, &x, 4);
            }
        }

#include "compiler.h"
#undef CMD_DEF
#undef JMP_DEF

        else if (!strcmp(pch, "end")) {
            x = 100;
            write(fd_write, &x, 1);
            has_no_end = false;
        }
        pch = strtok(NULL, " \n@");
    }
    close(fd_write);
    if (has_no_end) {
        printf("There is no 'end' command in script. Please, add the 'end' command\n");
        assert(0);
    }
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
    int cmdCount = 0;
    int tag = 0;
    char *pch = strtok(buf, "\n@");
    while (pch != NULL) {
        char *ptr = strstr(pch, ":");
        if (pch == ptr) {
            tag = atoi(ptr + 1);
            if (tag > MAX_TAG) {
                printf("MAX TAG IS 255");
                exit(-1);
            }
            tags[tag] = cmdCount;
        } else if (strstr(pch, "push") || strstr(pch, "pop") || strstr(pch, "jmp") || strstr(pch, "je") ||
                strstr(pch, "jne") || strstr(pch, "ja") || strstr(pch, "jae") || strstr(pch, "jb") ||
                strstr(pch, "jbe") || strstr(pch, "call")) {
            cmdCount += 2;
        } else {
            cmdCount++;
        }
        pch = strtok(NULL, "\n@");
    }
}