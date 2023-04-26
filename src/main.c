// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

#include "csv_lexer/csv_lexer.h"
#include "obj_funcs/objective_functions.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h> 
#include <math.h>

#define LEARNING_RATE 0.1

double sigmoid(double y) {
    return 1 / (1 + exp(-1 * y));
}

double predict(double *weights, double **point, int input_dim) {
    double y = 0;
    int i = 0;
    for (; i < input_dim; i++) {
        y += weights[i] * *point[i];
    }
    // add the bias
    y += weights[i];

    return sigmoid(y);
}


double evaluate_model(double *weights, double ***data, double *predictions, int num_data, int input_dim, int num_classes) {
    double mse = 0;
    for (int i = 0; i < num_data; i++) {
        double prediction = predict(weights, data[i], input_dim);
        // multiply by number of classes
        double target = *data[i][input_dim];
        mse += pow((target / num_classes) - prediction, 2.0);
        predictions[i] = prediction;
    }

    return mse / num_data;
}
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
    int num_classes = 0;
    char **classes = NULL;
    double ***data = lex_csv(file, &classes, &num_data, &num_cols, &num_classes);
    int input_dim = num_cols - 1; // last one is target
    double weights[input_dim];
    srand(time(NULL)); // set the seed value based on current time
    // srand(1);
    // add 1 for the bias
    for (int i = 0; i < input_dim + 1; i++) {
        weights[i] = ((double)rand()/(double)(RAND_MAX));
    }

    double predictions[num_data];
    double mse = evaluate_model(weights, data, predictions, num_data, input_dim, num_classes);
    printf("Error: %f\n", mse);

    for (int i = 0; i < num_data; i++) {
        for (int j = 0; j < num_cols; j++) {
            // printf("%f ", *data[i][j]);
            free(data[i][j]);
        }
        // printf("\n");
    }
    free(data);

    return 0;
}

