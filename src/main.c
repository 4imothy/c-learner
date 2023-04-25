// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

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

    getline(&buffer, &bufsize, myFile);
    char **header = NULL;
    char *token = strtok(buffer, ",");
    int num_cols = 0;
    // get the header
    while (token) {
        num_cols++;
        header = realloc(header, num_cols * sizeof(char *));
        header[num_cols - 1] = token;
        token = strtok(NULL, ",");
    }

    char ***lines= NULL;
    int num_lines = 0;
    while (getline(&buffer, &bufsize, myFile) != -1) {
        token = strtok(buffer, ",");
        // while there are more tokens in this line
        while (token) {
            int len = strlen(token);
            char **line = malloc(num_cols * sizeof(char *));
            int j = 0;
            while (token[len - 1] != '\n'){
                line[j] = malloc(strlen(token) + 1);
                strcpy(line[j], token);
                token = strtok(NULL, ",");
                len = strlen(token);
                j++;
            }
            // the current token is the target
            line[j] = malloc(strlen(token) + 1);
            strcpy(line[j], token);
            lines = realloc(lines, num_cols * (num_lines+1) * sizeof(char *));
            lines[num_lines] = line;
            num_lines++;
            token = strtok(NULL, ",");
        }
    }
    free(buffer);
    free(token);

    int tar_idx = num_cols - 1;
    for (int i = 0; i < num_lines; i++){
        printf("%s", lines[i][tar_idx]);
    }
    
    return 0;
}
