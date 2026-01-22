#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
    size_t rows;
    size_t cols;
    size_t strides;
    double *data;
} Matrix;