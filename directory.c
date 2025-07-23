#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "directory.h"
#include "file.h"

dir_t create_dir(char* name) {
    dir_t new_dir = {name, 
            0, (file_t *)malloc(100 * sizeof(file_t)), 
            (dir_t *)malloc(sizeof(dir_t)), 
            0, (dir_t *)malloc(100 * sizeof(dir_t))
    };

    return new_dir;
}

void free_dir(dir_t* dir) {
    free(dir->files);
    free(dir->children);
}

char* get_path_from_dir(dir_t* dir) {
    if (!dir) return "/";

    char* returning_path = (char *)calloc(1, sizeof(char));
    if (!returning_path) return NULL;

    dir_t* current = dir;
    int safety_counter = 0;

    while (current != NULL && safety_counter++ < 1000) {
        printf("%s ", current->name);
        const char* name = current->name ? current->name : "";

        size_t new_len = strlen(name) + strlen(returning_path) + 2;
        char* new_path = malloc(new_len);
        if (!new_path) {
            free(returning_path);
            return NULL;
        }

        snprintf(new_path, new_len, "/%s%s", name, returning_path);

        free(returning_path);
        returning_path = new_path;

        if (current == current->parent) {
            fprintf(stderr, "Cycle detected in directory structure.\n");
            break;
        }

        current = current->parent;
    }

    return returning_path;
}

void add_file(dir_t* dir, file_t* file) {
    file->path = get_path_from_dir(dir);

    dir->files[dir->file_count] = *file;
    dir->file_count++;
}

void add_subdir(dir_t* dir, dir_t* sub_dir) {
    sub_dir->parent = dir;
    dir->children[dir->child_count] = *sub_dir;
    dir->child_count++;
}

float dir_weight(dir_t* dir) {
    float current_weight = 0.0f;

    for (int i = 0 ; i < dir->file_count ; i++) {
        current_weight += dir->files[i].weight_kb;
    }

    for (int i = 0 ; i < dir->child_count ; i++) {
        current_weight += dir_weight(&dir->children[i]);
    }

    return current_weight;
}

void print_dir(dir_t* dir) {
    printf("%s\n", dir->name);

    for (int i = 0 ; i < dir->file_count ; i++) {
        printf("%d. %s - %f kb -- %s\n", (i + 1), dir->files[i].name, dir->files[i].weight_kb, dir->files[i].path);
    }

    printf("\n");

    for (int i = 0 ; i < dir->child_count ; i++) {
        print_dir(&dir->children[i]);
    }
}
