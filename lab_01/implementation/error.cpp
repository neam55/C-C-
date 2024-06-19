#include"error.h"

char *error_prompt(const error_t &rc)
{
    char *prompt = nullptr;
    if (rc == SUCCESS)
        prompt = (char*) "Success.";
    else if (rc == MEM_ERROR)
        prompt = (char*) "Memory allocation error occured.";
    else if (rc == IO_ERROR)
        prompt = (char*) "Input/output error occured.";
    else if (rc == ARGS_ERROR)
        prompt = (char*) "Invalid arguments.";
    else if (rc == EMPTY_MTX_ERROR)
        prompt = (char*) "Empty matrix occured during calculation.";
    else if (rc == READ_ERROR)
        prompt = (char*) "Failed to read object.";
    else if (rc == UNEVEN_MTX_ERROR)
        prompt = (char*) "Uneven matrix during multiplication occured.";
    else if (rc == EMPTY_OBJ_ERROR)
        prompt = (char*) "Input file is empty.";
    return prompt;
}
