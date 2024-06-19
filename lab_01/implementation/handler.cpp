#include"handler.h"

error_t command_handler(const comand_t &comand)
{
    static object_t obj;
    error_t rc = SUCCESS;
    if (comand.action == ACTION_TRANSITION)
        rc = obj_transition(obj, comand.transition);
    else if (comand.action == ACTION_ROTATE)
        rc = obj_rotate(obj, comand.rotate);
    else if (comand.action == ACTION_SCALE)
        rc = obj_scale(obj, comand.scale);
    else if (comand.action == ACTION_DRAW)
        rc = obj_draw(obj, comand.scene);
    else if (comand.action == ACTION_READ)
        rc = obj_load(obj, comand.filename);
    else if (comand.action == ACTION_CLEAR_SCENE)
        rc = scene_clear(comand.scene);
    else if (comand.action == ACTION_FREE_OBJ)
        rc = obj_free(obj);
    return rc;
}
