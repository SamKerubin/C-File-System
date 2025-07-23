#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include "file.h"

typedef struct dir_t {
    char* name;
    int file_count;
    file_t* files;
    struct dir_t* parent;
    int child_count;
    struct dir_t* children;
} dir_t;

dir_t create_dir(char* name);
void free_dir(dir_t* dir);
void add_file(dir_t* dir, file_t* file);
void add_subdir(dir_t* dir, dir_t* sub_dir);
float dir_weight(dir_t* dir);
void print_dir(dir_t* dir);

#endif