#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ***get_lines(FILE *file, int *nl, int *num_cols)
{
    char *buffer = NULL;
    size_t bufsize = 0;

    // num cols and num_lines set
    getline(&buffer, &bufsize, file);
    char **header = NULL;
    char *token = strtok(buffer, ",");
    // get the header
    int c = 0;
    while (token) {
        c++;
        header = realloc(header, c * sizeof(char *));
        header[c - 1] = token;
        token = strtok(NULL, ",");
    }

    *num_cols = c;

    char ***lines = NULL;
    int num_lines = 0;
    while (getline(&buffer, &bufsize, file) != -1) {
        token = strtok(buffer, ",");
        // while there are more tokens in this line
        while (token) {
            int len = strlen(token);
            char **line = malloc(*num_cols * sizeof(char *));
            int j = 0;
            while (token[len - 1] != '\n') {
                line[j] = malloc(strlen(token) + 1);
                strcpy(line[j], token);
                token = strtok(NULL, ",");
                len = strlen(token);
                j++;
            }
            // the current token is the target
            line[j] = malloc(strlen(token) + 1);
            strcpy(line[j], token);
            num_lines++;
            lines = realloc(lines, *num_cols * (num_lines) * sizeof(char *));
            lines[num_lines - 1] = line;
            token = strtok(NULL, ",");
        }
    }
    free(buffer);
    free(token);

    *nl = num_lines;
    return lines;
}

char **class_to_numeric(char ***lines, int *num_classes, int tar_idx,
                        int num_lines)
{
    char **classes = NULL;
    int c = 0;
    for (int i = 1; i < num_lines; i++) {
        int not_contained = 0;
        for (int j = 0; j < c; j++) {
            if (strcmp(lines[i][tar_idx], classes[j]) != 0) {
                not_contained++;
            }
        }
        if (not_contained == c) {
            c++;
            char *class = lines[i][tar_idx];
            classes = realloc(classes, c * sizeof(class));
            // add the null character to the end
            classes[c - 1] = malloc(strlen(class) + 1);
            strcpy(classes[c - 1], class);
        }
    }

    *num_classes = c;
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < *num_classes; j++) {
            if (strcmp(lines[i][tar_idx], classes[j]) == 0) {
                sprintf(lines[i][tar_idx], "%d\n", j);
                break;
            }
        }
    }
    return classes;
}

double ***lex_csv(FILE *file, char ***classes, int *num_data, int *num_cols,
                  int *num_classes)
{
    int num_lines = 0;
    char ***lines = get_lines(file, &num_lines, num_cols);

    int tar_idx = *num_cols - 1;
    *classes = class_to_numeric(lines, num_classes, tar_idx, num_lines);

    double ***data = malloc(num_lines * sizeof(double **));
    for (int i = 0; i < num_lines; i++) {
        data[i] = malloc(*num_cols * sizeof(double *));
        for (int j = 0; j < *num_cols; j++) {
            data[i][j] = malloc(sizeof(double));
            *data[i][j] = strtod(lines[i][j], NULL);
        }
    }
    *num_data = num_lines;

    // free up lines
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < *num_cols; j++) {
            free(lines[i][j]);
        }
    }
    free(lines);
    return data;
}
