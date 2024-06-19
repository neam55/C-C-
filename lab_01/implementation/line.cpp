#include"line.h"

int line_scan(FILE *f, line_t &line)
{
    int rc = (fscanf(f, "%lf; %lf; %lf;", &(line.p1.x), &(line.p1.y), &(line.p1.z)) == 3);
    if (rc)
        rc = (fscanf(f, "%lf; %lf; %lf;", &(line.p2.x), &(line.p2.y), &(line.p2.z)) == 3);
    return rc;
}
