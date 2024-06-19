#ifndef SCENE_H
#define SCENE_H

#include<QGraphicsScene>
#include"error.h"
#include"line.h"
typedef struct
{
    QGraphicsScene *scene;
    int display_width;
    int displsy_height;
} scene_t;

error_t scene_clear(const scene_t &scene);

error_t scene_draw_line(const scene_t &scene, const line_t &line);

error_t scene_draw_point(const scene_t &scene, const point_t &point);

#endif
