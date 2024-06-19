#include"affine_transformations.h"
matrix_t x_axis_rotate_mtx(double angle)
{
    angle *= M_PI / 180;
    double tmp [ACTION_MTX_ROWS][ACTION_MTX_COLS] = {
        { 1, 0, 0, 0 },
        { 0, cos(angle), -sin(angle), 0 },
        { 0, sin(angle), cos(angle), 0 },
        { 0, 0, 0, 1 }
    };
    matrix_t matrix;
    error_t rc = data_to_matrix(matrix, &(tmp[0][0]), ACTION_MTX_ROWS, ACTION_MTX_COLS);
    if (rc != SUCCESS)
    {
        matrix.cols = 0;
        matrix.rows = 0;
        matrix.data = nullptr;
    }
    return matrix;
}

matrix_t y_axis_rotate_mtx(double angle)
{
    angle *= M_PI / 180;
    double tmp [ACTION_MTX_ROWS][ACTION_MTX_COLS] = {
        { cos(angle), 0, -sin(angle), 0 },
        { 0, 1, 0, 0 },
        { sin(angle), 0, cos(angle), 0 },
        { 0, 0, 0, 1 }
    };
    matrix_t matrix;
    error_t rc = data_to_matrix(matrix, &(tmp[0][0]), ACTION_MTX_ROWS, ACTION_MTX_COLS);
    if (rc != SUCCESS)
    {
        matrix.cols = 0;
        matrix.rows = 0;
        matrix.data = nullptr;
    }
    return matrix;
}

matrix_t z_axis_rotate_mtx(double angle)
{
    angle *= M_PI / 180;
    double tmp [ACTION_MTX_ROWS][ACTION_MTX_COLS] = {
        { cos(angle), -sin(angle), 0, 0 },
        { sin(angle), cos(angle), 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
    matrix_t matrix;
    error_t rc = data_to_matrix(matrix, &(tmp[0][0]), ACTION_MTX_ROWS, ACTION_MTX_COLS);
    if (rc != SUCCESS)
    {
        matrix.cols = 0;
        matrix.rows = 0;
        matrix.data = nullptr;
    }
    return matrix;
}

matrix_t overall_rotate_mtx(double x_angle, double y_angle, double z_angle)
{
    matrix_t Rx = x_axis_rotate_mtx(x_angle);
    matrix_t Ry = y_axis_rotate_mtx(y_angle);
    matrix_t Rz = z_axis_rotate_mtx(z_angle);
    matrix_t result_1, result_2;
    matrix_mull(result_1, Rx, Ry);
    matrix_mull(result_2, Rz, result_1);
    matrix_destroy(Rx);
    matrix_destroy(Ry);
    matrix_destroy(Rz);
    matrix_destroy(result_1);
    return result_2;
}

matrix_t scale_mtx(double kx, double ky, double kz)
{
    double tmp[ACTION_MTX_ROWS][ACTION_MTX_COLS] = {
        {kx, 0, 0, 0},
        {0, ky, 0, 0},
        {0, 0, kz, 0},
        {0, 0, 0, 1}
    };
    matrix_t matrix;
    error_t rc = data_to_matrix(matrix, &(tmp[0][0]), ACTION_MTX_ROWS, ACTION_MTX_COLS);
    if (rc != SUCCESS)
    {
        matrix.cols = 0;
        matrix.rows = 0;
        matrix.data = nullptr;
    }
    return matrix;
}

matrix_t transition_mtx(double dx, double dy, double dz)
{
    double tmp[ACTION_MTX_ROWS][ACTION_MTX_COLS] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {dx, dy, dz, 1}
    };
    matrix_t matrix;
    error_t rc = data_to_matrix(matrix, &(tmp[0][0]), ACTION_MTX_ROWS, ACTION_MTX_COLS);
    if (rc != SUCCESS)
    {
        matrix.cols = 0;
        matrix.rows = 0;
        matrix.data = nullptr;
    }
    return matrix;
}

matrix_t point_to_vec(const point_t &point)
{
    double tmp[][ACTION_MTX_COLS] = {{point.x, point.y, point.z, 1}};
    matrix_t matrix;
    error_t rc = data_to_matrix(matrix, &(tmp[0][0]), sizeof(tmp) / sizeof(tmp[0]), sizeof(tmp[0])/sizeof(tmp[0][0]));
    if (rc != SUCCESS)
    {
        matrix.rows = 0;
        matrix.cols = 0;
        matrix.data = nullptr;
    }
    return matrix;
}

point_t vec_to_point(const matrix_t &vec)
{
    return {vec.data[0][0], vec.data[0][1], vec.data[0][2]};
}
