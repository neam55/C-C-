#ifndef HANDLER_H
#define HANDLER_H
#include"actions.h"
#include"scene.h"
#include"object.h"

typedef enum
{
    ACTION_TRANSITION,
    ACTION_SCALE,
    ACTION_ROTATE,
    ACTION_DRAW,
    ACTION_READ,
    ACTION_CLEAR_SCENE,
    ACTION_FREE_OBJ

} action_t;

typedef struct
{
    action_t action;
    scene_t scene;
    action_coef_t transition;
    action_coef_t scale;
    action_coef_t rotate;
    char *filename;
} comand_t;

error_t command_handler(const comand_t &comand);
#endif // HANDLER_H
