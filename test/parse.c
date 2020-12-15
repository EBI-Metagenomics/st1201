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
    printf("Field L would be %d\n", line.L);

    strcpy(field, row);
    sscanf(getfield(field, 2), "%lf", &line.Z_o);
    printf("Field Z_o would be %lf\n", line.Z_o);

    strcpy(field, row);
    sscanf(getfield(field, 3), "%lf", &line.a);
    printf("Field a would be %lf\n", line.a);

    strcpy(field, row);
    sscanf(getfield(field, 4), "%lf", &line.b);
    printf("Field b would be %lf\n", line.b);

    strcpy(field, row);
    /* sscanf(getfield(field, 6), "%" SCNu8, &line.y); */
    sscanf(getfield(field, 6), "%" SCNu64, &line.y);
    strcpy(field, row);
    printf("Field y would be %llu\n", line.y);

    strcpy(field, row);
    printf("Field yhex would be %s\n", getfield(field, 7));

    strcpy(field, row);
    sscanf(getfield(field, 8), "%lf", &line.x_r);
    printf("Field xr would be %lf\n", line.x_r);

    strcpy(field, row);
    sscanf(getfield(field, 9), "%lf", &line.S_f);
    printf("Field S_f would be %lf\n", line.S_f);

    strcpy(field, row);
    sscanf(getfield(field, 10), "%lf", &line.S_r);
    printf("Field S_r would be %lf\n", line.S_r);

    strcpy(field, row);
    sscanf(getfield(field, 11), "%lf", &line.x);
    printf("Field x would be %lf\n", line.x);

    return line;
}
