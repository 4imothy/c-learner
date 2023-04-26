// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

#include "csv_lexer/csv_lexer.h"
#include "obj_funcs/objective_functions.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO read the full CSV and make the data points the valid types

int main()
{
    // Order of the iris.data file
    //  Sepal Length, Sepal Width, Petal Length, Petal Width, Species
    FILE *file = NULL;

    if ((file = fopen("iris_data.csv", "r")) == NULL) {
        printf("Failed to read file\n");
        exit(1);
    }
    printf("File read successfully\n");

    int num_data = 0;
    int num_cols = 0;
    float ***data = lex_csv(file, &num_data, &num_cols);

    for (int i = 0; i < num_data; i++) {
        for (int j = 0; j < num_cols; j++) {
            printf("%f ", *data[i][j]);
        }
        printf("\n");
    }
    return 0;
}
