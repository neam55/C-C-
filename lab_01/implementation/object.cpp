#include"object.h"

static point_t obj_center(object_t &obj)
{
    point_t result = {.x=0, .y=0, .z=0};
    for (size_t i = 0; i < obj.lines_cnt; i++)
    {
        result.x += (obj.lines[i].p1.x + obj.lines[i].p2.x) / 2.0;
        result.y += (obj.lines[i].p1.y + obj.lines[i].p2.y) / 2.0;
        result.z += (obj.lines[i].p1.z + obj.lines[i].p2.z) / 2.0;
    }
    result.x /= obj.lines_cnt;
    result.y /= obj.lines_cnt;
    result.z /= obj.lines_cnt;
    return result;
}

static error_t _obj_fscan(FILE *f, object_t &obj)
{
    error_t rc = SUCCESS;
    size_t lines_cnt;
    if (fscanf(f, "%zu\n", &lines_cnt) != 1)
        rc = READ_ERROR;
    if ((rc == SUCCESS) && (lines_cnt == 0))
        rc = ARGS_ERROR;
    line_t *lines = (line_t *)calloc(lines_cnt, sizeof(line_t));
    if (lines == nullptr)
        rc = MEM_ERROR;
    for (size_t i = 0; (i < lines_cnt) && (rc == SUCCESS); i++)
        if (line_scan(f, lines[i]) != 1)
            rc = READ_ERROR;

    if (rc == SUCCESS)
    {
        obj.lines_cnt = lines_cnt;
        obj.lines = lines;
        obj.figure_center = obj_center(obj);
    }
    return rc;
}

static void _obj_transition(object_t &obj, const action_coef_t &coef)
{
    for (size_t i = 0; i < obj.lines_cnt; i++)
    {
        obj.lines[i].p1 = transition(obj.lines[i].p1, coef);
        obj.lines[i].p2 = transition(obj.lines[i].p2, coef);
    }
}

error_t obj_rotate(object_t &obj, const action_coef_t &coef)
{
    error_t rc = SUCCESS;
    if ((obj.lines_cnt == 0) || (obj.lines == nullptr))
        rc = EMPTY_OBJ_ERROR;
    if (rc == SUCCESS)
    {
        _obj_transition(obj, {-obj.figure_center.x, -obj.figure_center.y, -obj.figure_center.z});
        for (size_t i = 0; i < obj.lines_cnt; i++)
        {
            obj.lines[i].p1 = rotate(obj.lines[i].p1, coef);
            obj.lines[i].p2 = rotate(obj.lines[i].p2, coef);
        }
        _obj_transition(obj, {obj.figure_center.x, obj.figure_center.y, obj.figure_center.z});
    }
    return rc;
}

error_t obj_transition(object_t &obj, const action_coef_t &coef)
{
    error_t rc = SUCCESS;
    if ((obj.lines_cnt == 0) || (obj.lines == nullptr))
        rc = EMPTY_OBJ_ERROR;
    if (rc == SUCCESS)
    {
        for (size_t i = 0; i < obj.lines_cnt; i++)
        {
            obj.lines[i].p1 = transition(obj.lines[i].p1, coef);
            obj.lines[i].p2 = transition(obj.lines[i].p2, coef);
        }
        obj.figure_center = transition(obj.figure_center, coef);
    }
    return rc;
}

error_t obj_scale(object_t &obj, const action_coef_t &coef)
{
    error_t rc = SUCCESS;
    if ((obj.lines_cnt == 0) || (obj.lines == nullptr))
        rc = EMPTY_OBJ_ERROR;
    if (rc == SUCCESS)
    {
        _obj_transition(obj, {-obj.figure_center.x, -obj.figure_center.y, -obj.figure_center.z});
        for (size_t i = 0; i < obj.lines_cnt; i++)
        {
            obj.lines[i].p1 = scale(obj.lines[i].p1, coef);
            obj.lines[i].p2 = scale(obj.lines[i].p2, coef);
        }
        _obj_transition(obj, {obj.figure_center.x, obj.figure_center.y, obj.figure_center.z});
    }
    return rc;
}

error_t obj_load(object_t &obj, const char *filename)
{
    if ((obj.lines_cnt != 0) || (filename == nullptr))
        return ARGS_ERROR;
    FILE *input = fopen(filename, "r");
    if (input == nullptr)
        return IO_ERROR;
    error_t rc = SUCCESS;
    rc = _obj_fscan(input, obj);
    if (fclose(input) == EOF)
        rc = IO_ERROR;
    return rc;
}

error_t obj_draw(object_t &obj, const scene_t &scene)
{
    error_t rc = scene_clear(scene);
    if (rc == SUCCESS)
        for (size_t i = 0; i < obj.lines_cnt; i++)
            rc = scene_draw_line(scene, obj.lines[i]);
    if ((obj.lines != nullptr) && (rc == SUCCESS))
        rc = scene_draw_point(scene, obj.figure_center);
    return rc;
}

error_t obj_free(object_t &obj)
{
    free(obj.lines);
    obj.lines = nullptr;
    obj.lines_cnt = 0;
    return SUCCESS;

}
