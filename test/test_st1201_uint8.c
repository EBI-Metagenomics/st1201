#include "cass.h"
#include "st1201.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static const char *getfield(char *line, int num);

int main(void)
{
    FILE *stream = fopen(ST1201_TEST_DATA_FILEPATH, "r");
    cass_cond(stream != NULL);
    char line[256];
    char field[256];

    unsigned row = 1;
    cass_cond(fgets(line, 256, stream) != NULL);

    row++;
    while (fgets(line, 256, stream)) {
        printf("Line num: %u\n", row);
        row++;

        strcpy(field, line);
        int L = atoi(getfield(field, 1));
        printf("Field L would be %d\n", L);

        strcpy(field, line);
        double Z_o = 0.0;
        sscanf(getfield(field, 2), "%lf", &Z_o);
        printf("Field Z_o would be %lf\n", Z_o);

        double a = 0.0;
        strcpy(field, line);
        sscanf(getfield(field, 3), "%lf", &a);
        printf("Field a would be %lf\n", a);

        double b = 0.0;
        strcpy(field, line);
        sscanf(getfield(field, 4), "%lf", &b);
        printf("Field b would be %lf\n", b);

        uint8_t y = 0;
        strcpy(field, line);
        sscanf(getfield(field, 6), "%" SCNu8, &y);
        strcpy(field, line);
        printf("Field y would be %u\n", y);

        strcpy(field, line);
        printf("Field yhex would be %s\n", getfield(field, 7));

        double xr = 0.0;
        strcpy(field, line);
        sscanf(getfield(field, 8), "%lf", &xr);
        printf("Field xr would be %lf\n", xr);

        double S_f = 0.0;
        strcpy(field, line);
        sscanf(getfield(field, 9), "%lf", &S_f);
        printf("Field S_f would be %lf\n", S_f);

        double S_r = 0.0;
        strcpy(field, line);
        sscanf(getfield(field, 10), "%lf", &S_r);
        printf("Field S_r would be %lf\n", S_r);

        double x = 0.0;
        strcpy(field, line);
        sscanf(getfield(field, 11), "%lf", &x);
        printf("Field x would be %lf\n", x);

        if (x < a || b < x)
            continue;

        struct st1201_uint8 st1201;
        cass_cond(st1201_init_uint8(a, b, (unsigned)L, &st1201) == 0);
        cass_close(st1201.a, a);
        cass_close(st1201.b, b);
        cass_close(st1201.S_f, S_f);
        cass_close(st1201.S_r, S_r);
        cass_close(st1201.Z_o, Z_o);
        cass_equal_uint8(st1201_to_uint8(&st1201, x), y);
        cass_close(st1201_from_uint8(&st1201, y), xr);
    }

    fclose(stream);
    return cass_status();
}

static const char *getfield(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}
