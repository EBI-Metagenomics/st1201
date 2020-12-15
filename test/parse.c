#include "parse.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static const char *getfield(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

struct line parse_line(char const *row)
{
    char field[256];
    struct line line = {0, 0.0, 0.0, 0.0, 0, 0.0, 0.0, 0.0, 0.0};

    strcpy(field, row);
    line.L = atoi(getfield(field, 1));

    strcpy(field, row);
    sscanf(getfield(field, 2), "%lf", &line.Z_o);

    strcpy(field, row);
    sscanf(getfield(field, 3), "%lf", &line.a);

    strcpy(field, row);
    sscanf(getfield(field, 4), "%lf", &line.b);

    strcpy(field, row);
    sscanf(getfield(field, 6), "%" SCNu64, &line.y);

    strcpy(field, row);

    strcpy(field, row);
    sscanf(getfield(field, 8), "%lf", &line.x_r);

    strcpy(field, row);
    sscanf(getfield(field, 9), "%lf", &line.S_f);

    strcpy(field, row);
    sscanf(getfield(field, 10), "%lf", &line.S_r);

    strcpy(field, row);
    sscanf(getfield(field, 11), "%lf", &line.x);

    return line;
}
