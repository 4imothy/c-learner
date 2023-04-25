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

    int num_classes = 1;
    int tar_idx = num_cols - 1;
    // add the first one
    char **classes = malloc(num_classes * sizeof(char *));
    classes[num_classes - 1] = lines[0][tar_idx];
    for (int i = 1; i < num_lines; i++){
        int not_contained = 0;
        for (int j = 0; j < num_classes; j++) {
            if (strcmp(lines[i][tar_idx], classes[j]) != 0) {
                not_contained++;
            }
        }
        if (not_contained == num_classes){
            num_classes++;
            classes = realloc(classes, num_classes * sizeof(char *));
            classes[num_classes - 1] = malloc(sizeof(lines[i][tar_idx]));
            strcpy(classes[num_classes - 1], lines[i][tar_idx]);
        }
    }

    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_classes; j++) {
            if (strcmp(lines[i][tar_idx], classes[j]) == 0) {
                sprintf(lines[i][tar_idx], "%d\n", j);
                break;
            }
        }
    } 

    float ***data = malloc(num_lines * sizeof(float **));
    for (int i = 0; i < num_lines; i++) {
        data[i] = malloc(num_cols * sizeof(float *));
        for (int j = 0; j < num_cols; j++) {
            data[i][j] = malloc(sizeof(float));
            *data[i][j] = strtof(lines[i][j], NULL);
        }
    }

    // free up lines
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_cols; j++) {
            free(lines[i][j]);
        }
    }
    free(lines);
    for (int i = 0; i < num_lines; i++) {
        // for (int j = 0; j < num_cols; j++) {
            printf("%f\n", *data[i][4]);
        // }
    }

    return 0;
}
