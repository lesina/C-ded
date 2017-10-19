#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <unistd.h>
#include <cstring>
#include "rfile.h"

#define FD_ERROR_OPEN(fd) if (fd == -1) { perror("open"); exit(-1); }

const char *computer_commands = "comp";
const int MAX_N_TAGS = 65536;

void write_to_file(int *, char *);

void collect_tags(int *, char *);

int main() {
    printf("Please, enter the name of asm script: ");
    char *file_script = (char *) malloc(FILENAME_MAX);
    scanf("%s", file_script);

    errno = 0;
    int fd_read = open(file_script, O_RDONLY);
    FD_ERROR_OPEN(fd_read);

    long int size_of_file = get_file_size(fd_read);

    char *buf = (char *) calloc(size_of_file, sizeof(char));

    read(fd_read, buf, size_of_file);
    close(fd_read);
    int *tags = (int *) calloc(MAX_N_TAGS, sizeof(int));
    collect_tags(tags, buf);

    //TODO: WTF???? I should reread this shit!
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
    bool has_no_end = true;
    char *pch = strtok(buf, " \n@");
    while (pch != NULL) {
        if (!strcmp(pch, "push")) {
            write(fd_write, "1", 1);
            pch = strtok(NULL, " \n@");
            if (!strcmp(pch, "ax")) {
                write(fd_write, "0 51", 4);
            } else if (!strcmp(pch, "bx")) {
                write(fd_write, "0 52", 4);
            } else if (!strcmp(pch, "cx")) {
                write(fd_write, "0 53", 4);
            } else if (!strcmp(pch, "dx")) {
                write(fd_write, "0 54", 4);
            } else {
                write(fd_write, " ", 1);
                write(fd_write, pch, strlen(pch));
            }
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "pop")) {
            write(fd_write, "20", 2);
            pch = strtok(NULL, " \n@");
            if (!strcmp(pch, "ax")) {
                write(fd_write, " 51", 3);
            } else if (!strcmp(pch, "bx")) {
                write(fd_write, " 52", 3);
            } else if (!strcmp(pch, "cx")) {
                write(fd_write, " 53", 3);
            } else if (!strcmp(pch, "dx")) {
                write(fd_write, " 54", 3);
            }
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "jmp")) {
            write(fd_write, "60 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "je")) {
            write(fd_write, "61 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "jne")) {
            write(fd_write, "62 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "jae")) {
            write(fd_write, "63 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "ja")) {
            write(fd_write, "64 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "jb")) {
            write(fd_write, "65 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "jbe")) {
            write(fd_write, "66 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "call")) {
            write(fd_write, "70 ", 3);
            pch = strtok(NULL, " \n@");
            snprintf(tag, sizeof(tag), "%d", tags[atoi(pch + 1)]);
            write(fd_write, tag, strlen(tag));
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "ret")) {
            write(fd_write, "71 ", 3);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "mul")) {
            write(fd_write, "2", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "sub")) {
            write(fd_write, "3", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "sqrt")) {
            write(fd_write, "4", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "add")) {
            write(fd_write, "5", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "div")) {
            write(fd_write, "6", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "sin")) {
            write(fd_write, "7", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "cos")) {
            write(fd_write, "8", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "out")) {
            write(fd_write, "9", 1);
            write(fd_write, "\n", 1);
        } else if (!strcmp(pch, "end")) {
            write(fd_write, "100", 3);
            write(fd_write, "\n", 1);
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
            tags[tag] = cmdCount;
        } else if (strstr(pch, "push") || strstr(pch, "pop")) {
            cmdCount += 2;
        } else {
            cmdCount++;
        }
        pch = strtok(NULL, "\n@");
    }
}