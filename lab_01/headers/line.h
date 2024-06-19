#ifndef LINE_H
#define LINE_H

#include<stdio.h>
#include"point.h"

typedef struct
{
    point_t p1;
    point_t p2;
} line_t;

int line_scan(FILE *f, line_t &line);

#endif
