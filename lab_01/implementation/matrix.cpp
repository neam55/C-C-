#include<string.h>
#include"matrix.h"
#include<stdio.h>

error_t matrix_destroy(matrix_t &matrix)
{
    free(matrix.data[0]);
    free(matrix.data);
    matrix.cols = 0;
    matrix.rows = 0;
    return SUCCESS;
}

error_t matrix_create(matrix_t &matrix, const size_t rows, const size_t cols)
{
    error_t rc = SUCCESS;
    matrix.cols = cols;
    matrix.rows = rows;
    matrix.data = (double**)calloc(rows, sizeof(double *));
    if (!matrix.data)
        rc = MEM_ERROR;
    double *data = (double*)calloc(rows * cols, sizeof(double));
    if (!data)
    {
        free(matrix.data);
        rc = MEM_ERROR;
    }
    if (rc == SUCCESS)
    {
        for (size_t i = 0; i < rows; i++)
            matrix.data[i] = &data[i * cols];
    }
    return rc;
}


error_t data_to_matrix(matrix_t &dst, double *data, const size_t rows, const size_t cols)
{
    error_t rc = SUCCESS;
    rc = matrix_create(dst, rows, cols);
    if (rc == SUCCESS)
        memmove(dst.data[0], data, rows * cols * sizeof(dst.data[0]));
   return rc;
}

error_t matrix_mull(matrix_t &dst, const matrix_t &multiplier_1,  const matrix_t &multiplier_2)
{
    error_t rc = SUCCESS;
    if (multiplier_1.cols != multiplier_2.rows)
        rc = UNEVEN_MTX_ERROR;

    if (multiplier_1.cols == 0 || multiplier_1.rows == 0 || multiplier_2.cols == 0 || multiplier_2.rows == 0)
        rc = EMPTY_MTX_ERROR;

    if (rc == SUCCESS)
        rc = matrix_create(dst, multiplier_1.rows, multiplier_2.cols);

    if (rc == SUCCESS)
    {
        for (size_t i = 0; i < multiplier_1.rows; i++)
        {
            for (size_t j = 0; j < multiplier_2.cols; j++)
            {
                dst.data[i][j] = 0;
                for (size_t k = 0; k < multiplier_1.cols; k++)
                    dst.data[i][j] += multiplier_1.data[i][k] * multiplier_2.data[k][j];
            }
        }
    }
    return rc;
}
