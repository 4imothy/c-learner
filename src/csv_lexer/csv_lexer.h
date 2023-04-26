#ifndef LEX_CSV_H
#define LEX_CSV_H

#include <stdio.h>
#include <stdlib.h>

double ***lex_csv(FILE *file, char ***classes, int *num_data, int *num_cols,
                  int *num_classes);

#endif
