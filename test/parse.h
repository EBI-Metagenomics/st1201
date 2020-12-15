#ifndef ST1201_TEST_PARSE_H
#define ST1201_TEST_PARSE_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

struct line
{
    int L;
    double Z_o;
    double a;
    double b;
    uint64_t y;
    double x_r;
    double S_f;
    double S_r;
    double x;
};

struct line parse_line(char const *row);

#endif
