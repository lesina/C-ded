#include "rfile.h"

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
//! Gets size of file in bytes
//!
//! @param  [in]    file    file pointer
//!
//! @return Size of file in bytes
//-------------------------------------------

size_t get_file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t res = ftell(file);
    rewind(file);
    return res;
}

//-------------------------------------------
//! Counts lines in text
//!
//! @param  [in]    buf    buffer with the whole text and every symbol
//!
//! @return Number of lines in text
//-------------------------------------------

size_t count_lines(const char *buf) {
    assert(buf);

    size_t number_of_lines = 1, i = 0;

    while (buf[i]) {
        if (buf[i] == '\n') {
            number_of_lines++;
        }
        i++;
    }

    return number_of_lines;
}