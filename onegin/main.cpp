#include <iostream>
#include <sys/stat.h>

long int getFileSize(const char *);

long int getNumberOfCharacters(FILE *);

int main() {

    printf("Sorting english version of Zhenya Onegin\n"
                   "1.1 (c) Lesha\n");

    const char *filename = "test";
    FILE *file = fopen(filename, "rb");
    long int number_of_characters = getNumberOfCharacters(file);
    long int size_of_file = getFileSize(filename);

    printf("%ld", size_of_file);

    return 0;
}

long int getFileSize(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
}

long int getNumberOfCharacters(FILE *file) {
    fseek(file, 0, SEEK_END);
    return ftell(file);
}