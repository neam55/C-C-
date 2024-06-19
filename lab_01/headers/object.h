#ifndef OBJECT_H
#define OBJECT_H

#include<stdlib.h>
#include"error.h"
#include"line.h"
#include"actions.h"
#include"scene.h"

typedef struct
{
    size_t lines_cnt;
    line_t *lines;
    point_t figure_center;
} object_t;

error_t obj_rotate(object_t &obj, const action_coef_t &coef);

error_t obj_transition(object_t &obj, const action_coef_t &coef);

error_t obj_scale(object_t &obj, const action_coef_t &coef);

error_t obj_load(object_t &obj, const char *filename);

error_t obj_draw(object_t &obj, const scene_t &scene);

error_t obj_free(object_t &obj);


#endif
