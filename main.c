#include <stdio.h>
#include <stdlib.h>
#include "directory.h"
#include "file.h"

int main() {
    dir_t dir = create_dir("Main Dir");
    dir_t subdir = create_dir("Sub Dir 1");
    file_t file = create_file("File 1", 5.0f);
    add_subdir(&dir, &subdir);
    add_file(&subdir, &file);

    // print_dir(&dir);
    // printf("%f kb\n", dir_weight(&dir));

    free_dir(&dir);
    free_dir(&subdir);
    free_file(&file);
    return 0;
}