#include <string.h>

int num_columns(char *line)
{
    int count = 0;
    for (unsigned long i = 0; i < strlen(line); i++) {
        if (line[i] == ',') {
            count++;
        }
    }
    return count + 1;
}
