#include"actions.h"


point_t action_apply(const point_t &point, const matrix_t &action_matrix)
{
    matrix_t vec = point_to_vec(point), tmp;
    matrix_mull(tmp, vec, action_matrix);
    matrix_destroy(vec);
    point_t result = vec_to_point(tmp);
    matrix_destroy(tmp);
    return result;
}

point_t transition(const point_t &point, const action_coef_t &coef)
{
    matrix_t matrix = transition_mtx(coef.x, coef.y, coef.z);
    point_t result = action_apply(point, matrix);
    matrix_destroy(matrix);
    return result;
}

point_t rotate(const point_t &point, const action_coef_t &coef)
{
    matrix_t matrix = overall_rotate_mtx(coef.x, coef.y, coef.z);
    point_t result = action_apply(point, matrix);
    matrix_destroy(matrix);
    return result;
}

point_t scale(const point_t &point, const action_coef_t &coef)
{
    matrix_t matrix = scale_mtx(coef.x, coef.y, coef.z);
    point_t result = action_apply(point, matrix);
    matrix_destroy(matrix);
    return result;
}
