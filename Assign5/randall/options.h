#ifndef OPTION_H // include guard
#define OPTION_H
#include <stdbool.h>

struct OptStruct{
    int input_type;
    int output_type;
    char *file_path;
    long long block_size;
    long long nbytes;
};

bool ProcessOptions(int argc, char **argv, struct OptStruct *ptr_opts);

#endif