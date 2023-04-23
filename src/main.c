// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "obj_funcs/objective_functions.h"

int main() {
    //Order of the iris.data file
    // Sepal Length, Sepal Width, Petal Length, Petal Width, Species
    what();

    int p = 0;

    FILE *myFile = NULL;

    myFile = fopen("iris.data", "r");

    if (myFile == NULL) {
      exit(1);
    }

    if (myFile != NULL) {
      printf("File read successfully\n");
    }
    char *buffer = NULL;
    size_t bufsize = 0;

    while (getline(&buffer, &bufsize, myFile) != -1) {
      char *token = strtok(buffer, ",");
      while (token) {
          printf("%s ", token);
          token = strtok(NULL, ",");
      }
      printf("\n");
    }
    free(buffer);
    return 0;
}