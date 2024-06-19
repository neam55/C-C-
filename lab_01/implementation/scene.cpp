#include"scene.h"

error_t scene_clear(const scene_t &scene)
{
    error_t rc = SUCCESS;
    if (scene.scene == nullptr)
        rc = ARGS_ERROR;
    if (rc == SUCCESS)
        scene.scene->clear();
    return rc;
}

error_t scene_draw_line(const scene_t &scene, const line_t &line)
{
    error_t rc = SUCCESS;
    if (scene.scene == nullptr)
        rc = ARGS_ERROR;
    if (rc == SUCCESS)
        scene.scene->addLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y);
    return rc;
}

error_t scene_draw_point(const scene_t &scene, const point_t &point)
{
    error_t rc = SUCCESS;
    if (scene.scene == nullptr)
        rc = ARGS_ERROR;
    if (rc == SUCCESS)
        scene.scene->addEllipse(point.x - 5, point.y - 5, 10, 10);
    return rc;
}
