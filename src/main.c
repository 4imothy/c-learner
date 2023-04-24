// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

#include "obj_funcs/objective_functions.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Order of the iris.data file
    //  Sepal Length, Sepal Width, Petal Length, Petal Width, Species
    FILE *myFile = NULL;

    myFile = fopen("iris_data.csv", "r");

    if (myFile == NULL) {
        printf("Failed to read file\n");
        exit(1);
    }

    if (myFile != NULL) {
        printf("File read successfully\n");
    }
    char *buffer = NULL;
    size_t bufsize = 0;
    // read the header
    // if getline(&buffer, &bufsize, myFile) != -1 {
    //     header = strok(buffer, ",");
    // }

    // read the remaining
    while (getline(&buffer, &bufsize, myFile) != -1) {
        // printf("%d\n", num_columns(buffer));
        char *token = strtok(buffer, ",");
        while (token) {
            // printf("%s", token);
            // token = strtok(NULL, ",");
        }
    }
    free(buffer);
    return 0;
}
