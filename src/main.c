// SPDX-License-Identifier: GPL-3.0-only
// AUTHOR: Timothy Cronin

#include "csv_lexer/csv_lexer.h"
#include "utils/utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEARNING_RATE 0.1
#define CONVERGENCE_BOUND 0.01

void update(double ***data, double *weights, double *predictions, int num_data,
            int input_dim)
{
    double coef = (-2 * LEARNING_RATE) / num_data;
    // = to input_dim for bias
    for (int i = 0; i <= input_dim; i++) {
        double sum = 0;
        for (int j = 0; j < num_data; j++) {
            sum += ((*data[j][input_dim] / 3) - predictions[j]) *
                   (1 - predictions[j]) * predictions[j] * (*data[j][i] / 3);
        }
        weights[i] -= (sum *= coef);
    }
}

double sigmoid(double y) { return 1 / (1 + exp(-1 * y)); }

double predict(double *weights, double **point, int input_dim)
{
    double y = 0;
    int i = 0;
    for (; i < input_dim; i++) {
        y += weights[i] * *point[i];
    }
    // add the bias
    y += weights[i];

    return sigmoid(y);
}

double evaluate_model(double *weights, double ***data, double *predictions,
                      int num_data, int input_dim, int num_classes)
{
    double mse = 0;
    for (int i = 0; i < num_data; i++) {
        double prediction = predict(weights, data[i], input_dim);
        predictions[i] = prediction;
        // multiply by number of classes
        double target = *data[i][input_dim];
        mse += pow((target / num_classes) - prediction, 2.0);
    }

    return (mse / num_data);
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
    double ***data =
        lex_csv(file, &classes, &num_data, &num_cols, &num_classes);
    int input_dim = num_cols - 1; // last one is target
    double weights[input_dim];
    srand(time(NULL)); // set the seed value based on current time
    // add 1 for the bias
    for (int i = 0; i <= input_dim + 1; i++) {
        weights[i] = ((double)rand() / (double)(RAND_MAX));
    }

    bool conv = false;
    int num_iter = 0;
    while (!conv) {
        double predictions[num_data];
        double mse = evaluate_model(weights, data, predictions, num_data,
                                    input_dim, num_classes);
        double delta_w[input_dim];
        double delta_b;
        update(data, weights, predictions, num_data, input_dim);

        num_iter++;
        printf("Error: %f\n", mse);
        if (mse < CONVERGENCE_BOUND) {
            conv = true;
        }
    }
    printf("Converged After: %d Iterations\n", num_iter);

    // Free things up
    for (int i = 0; i < num_data; i++) {
        for (int j = 0; j < num_cols; j++) {
            free(data[i][j]);
        }
    }
    free(data);
    for (int i = 0; i < num_classes; i++) {
        free(classes[i]);
    }
    free(classes);

    return 0;
}
