#ifndef MATRIX_H
#define MATRIX_H

#include<stdlib.h>
#include"error.h"

typedef struct
{
    size_t rows;
    size_t cols;
    double **data;
} matrix_t;

error_t matrix_create(matrix_t &matrix, const size_t rows, const size_t cols);

error_t matrix_destroy(matrix_t &matrix);

error_t data_to_matrix(matrix_t &dst, double *data, const size_t rows, const size_t cols);

error_t matrix_mull(matrix_t &dst, const matrix_t &multiplier_1,  const matrix_t &multiplier_2);

#endif

