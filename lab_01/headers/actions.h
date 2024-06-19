#ifndef ACTIONS_H
#define ACTIONS_H
#include"affine_transformations.h"

typedef struct
{
    double x;
    double y;
    double z;
} action_coef_t;


point_t transition(const point_t &point, const action_coef_t &coef);

point_t rotate(const point_t &point, const action_coef_t &coef);

point_t scale(const point_t &point, const action_coef_t &coef);

point_t action_apply(const point_t &point, const matrix_t &action_matrix);

#endif
