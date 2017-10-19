//
// Created by les on 10/16/17.
//

#ifndef ONEGIN_RFILE_H
#define ONEGIN_RFILE_H

#include <iostream>
#include <sys/stat.h>
#include <assert.h>

long int get_file_size(int);

size_t get_file_size(FILE *);

size_t count_lines(const char *);

#endif //ONEGIN_RFILE_H
