#ifndef _FILE_H_
#define _FILE_H_

typedef struct file_t {
    char* path;
    char* name;
    float weight_kb;
} file_t;

file_t create_file(char* name, float weight);
void free_file(file_t* file);

#endif