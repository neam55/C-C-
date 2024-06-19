#ifndef AFFINE_TRANSFORMATIONS_H
#define AFFINE_TRANSFORMATIONS_H

#include<math.h>
#include"matrix.h"
#include"point.h"
#include"error.h"

#define _USE_MATH_DEFINES
#define ACTION_MTX_ROWS 4
#define ACTION_MTX_COLS 4

matrix_t x_axis_rotate_mtx(double angle);

matrix_t y_axis_rotate_mtx(double angle);

matrix_t z_axis_rotate_mtx(double angle);

matrix_t overall_rotate_mtx(double x_angle, double y_angle, double z_angle);

matrix_t scale_mtx(double kx, double ky, double kz);

matrix_t transition_mtx(double dx, double dy, double dz);

matrix_t point_to_vec(const point_t &point);

point_t vec_to_point(const matrix_t &vec);

#endif
