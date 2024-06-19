#ifndef ERROR_H
#define ERROR_H

typedef enum
{
    SUCCESS,
    READ_ERROR,
    MEM_ERROR,
    UNEVEN_MTX_ERROR,
    EMPTY_MTX_ERROR,
    ARGS_ERROR,
    EMPTY_OBJ_ERROR,
    IO_ERROR
} error_t;


char *error_prompt(const error_t &rc);

#endif
