// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

#include "obj_funcs/objective_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Order of the iris.data file
    //  Sepal Length, Sepal Width, Petal Length, Petal Width, Species
    what();

    FILE *myFile = NULL;

    myFile = fopen("iris.data", "r");

    if (myFile == NULL) {
        exit(1);
    }

    if (myFile != NULL) {
        printf("File read successfully\n");
    }
    else {
        printf("hello");
    }
    char *buffer = NULL;
    size_t bufsize = 0;

    while (getline(&buffer, &bufsize, myFile) != -1) {
        char *token = strtok(buffer, ",");
        while (token) {
            printf("%s", token);
            token = strtok(NULL, ",");
        }
    }
    free(buffer);
    return 0;
}
