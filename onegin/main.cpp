#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <cstring>
#include "rfile.h"

#define FD_ERROR_OPEN(fd) if (fd == -1) { perror("open"); exit(-1); }

const char *poem = "test";
const char *dict = "dict";
const char *rifm = "rifm";

struct Verse {
    char *text;
    size_t length_of_verse = 0;
};

void list_of_string(Verse [], char *);

int compare(const void *, const void *);

int compare_from_end(const void *, const void *);

void write_to_file(Verse *, size_t, int);

void sorted_writef(const char *, Verse *, size_t, int (*compare)(const void *, const void *));

int main() {

    printf("Sorting english version of Zhenya Onegin\n"
                   "1.2 (c) Lesha\n");

    errno = 0;
    int fd = open(poem, O_RDONLY);
    FD_ERROR_OPEN(fd);

    long int size_of_file = get_file_size(fd);

    char *buf = (char *) calloc(size_of_file + 1, sizeof(char));
    assert(buf);

    read(fd, buf, size_of_file);
    close(fd);

    size_t number_of_lines = count_lines(buf);
    Verse verse[number_of_lines];

    list_of_string(verse, buf);

    sorted_writef(dict, verse, number_of_lines, compare);
    sorted_writef(rifm, verse, number_of_lines, compare_from_end);

    return 0;
}

//-------------------------------------------
//! Makes list of pointers to the begins of every line
//!
//! @param  [in]    buf     buffer with the whole text and every symbol
//! @param  [out]   verse   structure with the pointer to the begin of the verse
//!
//! @return list of pointers to the begins of every line and lengths of every verse
//-------------------------------------------

void list_of_string(Verse verse[], char *buf) {
    assert(buf);

    int i = 0, line = 1;
    size_t length = 1;
    verse[0].text = buf;

    while (buf[i]) {
        if (buf[i] == '\n') {
            verse[line].text = buf + i + 1;
            verse[line - 1].length_of_verse = length - 1;
            length = 0;
            line++;
        }
        length++;
        i++;
    }

    verse[line - 1].length_of_verse = length;
}

//-------------------------------------------
//! function of comparison strings in qsort
//!
//! \param  [in]    a   a-verse
//! \param  [in]    b   b-verse
//!
//! \return result of function srtcmp
//-------------------------------------------

int compare(const void *a, const void *b) {
    assert(a);
    assert(b);
    return strcmp(((Verse *) a)->text, ((Verse *) b)->text);
}

//-------------------------------------------
//! function of comparison strings (from the end) in qsort
//!
//! \param  [in]    a   a-verse
//! \param  [in]    b   b-verse
//!
//! \return >0 if a>b; <0 if a<b; 0 if a==b;
//-------------------------------------------

int compare_from_end(const void *a, const void *b) {
    assert(a);
    assert(b);

    Verse *first_verse = (Verse *) a;
    Verse *second_verse = (Verse *) b;

    int pos_in_end_a = first_verse->length_of_verse;
    int pos_in_end_b = second_verse->length_of_verse;

    while (pos_in_end_a && pos_in_end_b) {
        if (first_verse->text[pos_in_end_a] > second_verse->text[pos_in_end_b]) {
            return 1;
        } else if (first_verse->text[pos_in_end_a] < second_verse->text[pos_in_end_b]) {
            return -1;
        } else {
            pos_in_end_a--;
            pos_in_end_b--;
        }
    }

    return pos_in_end_b - pos_in_end_a;
}

//-------------------------------------------
//! Writes strings to file
//!
//! \param  [in]    verse           list of verses with pointers to the begin of every line of peom
//! \param  [in]    number_of_lines number of strings in text
//! \param  [in]    fd              file descriptor where we write text
//!
//! \return file with text
//-------------------------------------------

void write_to_file(Verse *verse, size_t number_of_lines, int fd) {
    assert(verse);

    for (int i = 0; i < number_of_lines; i++) {
        write(fd, verse[i].text, verse[i].length_of_verse + 1);
    }
}

//-------------------------------------------
//! Sorting and writing the text, based on function compare
//!
//! \param  [in]    filename
//! \param  [in]    verse
//! \param  [in]    number_of_lines
//! \param  [in]    cmp
//!
//! \return file with ordered text
//-------------------------------------------

void sorted_writef(const char *filename, Verse *verse, size_t number_of_lines, int (*cmp)(const void *, const void *)) {
    assert(filename);
    assert(verse);
    assert(cmp);

    qsort(verse, number_of_lines, sizeof(verse[0]), cmp);
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    FD_ERROR_OPEN(fd);
    write_to_file(verse, number_of_lines, fd);
    close(fd);
}