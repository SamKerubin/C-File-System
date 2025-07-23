#include <stdlib.h>
#include "file.h"

file_t create_file(char* name, float weight) {
    file_t new_file = {name, name, weight};
    return new_file;
}

void free_file(file_t* file) {
    free(file->path);
    free(file->name);
}