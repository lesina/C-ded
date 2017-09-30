#include <iostream>
#include <sys/stat.h>
#include <cassert>
#include <cmath>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

long int get_file_size(const char *);

long int get_number_of_characters(FILE *);

size_t count_lines(const char *);

void list_of_string(char **, char *);

int compare(const void *, const void *);

int main() {

    printf("Sorting english version of Zhenya Onegin\n"
                   "1.1 (c) Lesha\n");

    const char *filename = "test";
    FILE *file = fopen(filename, "rb");
    int fd = open(filename, O_RDONLY);
    assert(std::isfinite(fd));
    assert(file);

    long int number_of_characters = get_number_of_characters(file);
    long int size_of_file = get_file_size(filename);
    assert(std::isfinite(number_of_characters));
    assert(std::isfinite(size_of_file));

    char buf[number_of_characters];
    read(fd, buf, size_of_file);

    size_t number_of_lines = count_lines(buf);
    assert(std::isfinite(number_of_lines));
    char *text[number_of_lines];

    list_of_string(text, buf);
    qsort(text, number_of_lines, sizeof(text[0]), compare);

    return 0;
}

//-------------------------------------------
//! Gets size of file in bytes
//!
//! @param  [in]    filename    name of file with what we are working
//!
//! @return Size of file in bytes
//-------------------------------------------

long int get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

//-------------------------------------------
//! Gets number of characters in file
//!
//! @param  [in]    file    file-pointer
//!
//! @return Number of characters
//-------------------------------------------

long int get_number_of_characters(FILE *file) {
    fseek(file, 0, SEEK_END);
    return ftell(file);
}

//-------------------------------------------
//! Counts lines in text
//!
//! @param  [in]    buf    buffer with the whole text and every symbol
//!
//! @return Number of lines in text
//-------------------------------------------

size_t count_lines(const char *buf) {
    size_t number_of_lines = 1, i = 0;
    while (buf[i]) {
        if (buf[i] == '\n') {
            number_of_lines++;
        }
        i++;
    }
    return number_of_lines;
}

//-------------------------------------------
//! Makes list of pointers to the begins of every line
//!
//! @param  [in]    buf     buffer with the whole text and every symbol
//! @param  [out]   text    list of pointers to the begins of every line
//!
//! @return list of pointers to the begins of every line
//-------------------------------------------

void list_of_string(char **text, char *buf) {
    int i = 1, line = 1;
    text[0] = buf;
    while (buf[i]) {
        if (buf[i] == '\n') {
            text[line] = buf + i + 1;
            line++;
        }
        i++;
    }
}

//-------------------------------------------
//! function of comparison strings in qsort
//!
//! \param  [in]    a   a-string
//! \param  [out]   b   b-string
//!
//! \return result of function srtcmp
//-------------------------------------------

int compare(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}