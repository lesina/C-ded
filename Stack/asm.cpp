#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cassert>
#include <unistd.h>
#include <cstring>

#define FD_ERROR_OPEN(fd) if (fd == -1) { perror("open"); exit(-1); }

const char *computer_commands = "comp";

long int get_file_size(int);

void write_to_file(char*);

int main() {
    printf("Please, enter the name of asm script: ");
    char *file_script = (char *) malloc(FILENAME_MAX);
    scanf("%s", file_script);

    errno = 0;
    int fd_read = open(file_script, O_RDONLY);
    FD_ERROR_OPEN(fd_read);

    long int size_of_file = get_file_size(fd_read);

    char buf[size_of_file];
    read(fd_read, buf, size_of_file);
    close(fd_read);

    write_to_file(buf);

    return 0;
}

//-------------------------------------------
//! Gets size of file in bytes
//!
//! @param  [in]    fd    file descriptor
//!
//! @return Size of file in bytes
//-------------------------------------------

long int get_file_size(int fd) {
    struct stat st;
    if (fstat(fd, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

//-------------------------------------------
//! Writing script in computer code
//!
//! @param  [in]    buf     the whole script
//!
//! @return File with understandable code
//-------------------------------------------

void write_to_file(char *buf) {
    int fd_write = open(computer_commands, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FD_ERROR_OPEN(fd_write);

    bool has_no_end = true;
    char *pch = strtok(buf, " \n@");
    while (pch != NULL) {
        if (!strcmp(pch, "push")) {
            write(fd_write, "1 ", 2);
            pch = strtok(NULL, " \n@");
            write(fd_write, pch, strlen(pch));
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
            write(fd_write, "-1", 2);
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