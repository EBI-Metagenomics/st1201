#include "st1201.h"
#include "cass.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void test_st1201_uint8(void);
static const char *getfield(char *line, int num);

int main()
{
    test_st1201_uint8();
    return cass_status();
}

static void test_st1201_uint8(void)
{
    FILE *stream = fopen("small.csv", "r");
    cass_cond(stream != NULL);
    char line[256];
    char field[256];

    cass_cond(fgets(line, 256, stream) != NULL);

    while (fgets(line, 256, stream)) {

        strcpy(field, line);
        int L = atoi(getfield(field, 1));
        if (L > 1)
            continue;
        printf("Field L would be %d\n", L);

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

        struct st1201_uint8 st1201;
        st1201_init_uint8(a, b, (unsigned)L, &st1201);
        cass_close(st1201.S_f, S_f);
        cass_close(st1201.S_r, S_r);
        cass_equal_uint8(st1201_to_uint8(&st1201, x), y);
        cass_close(st1201_from_uint8(&st1201, y), xr);
        /* cass_equal_uint16(st1201_to_uint8(&st1201, 1.5), 16384); */
        /* cass_equal_uint16(st1201_to_uint8(&st1201, 2.0), 32768); */
    }

    fclose(stream);
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