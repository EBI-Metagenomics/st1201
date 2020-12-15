#include "cass.h"
#include "parse.h"
#include "st1201.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void test_st1201_uint8(struct line line);
static void test_st1201_uint16(struct line line);
static void test_st1201_uint32(struct line line);
static void test_st1201_uint64(struct line line);

int main(void)
{
    FILE *stream = fopen(ST1201_TEST_DATA_FILEPATH, "r");
    cass_cond(stream != NULL);
    char row[256];

    unsigned nrow = 1;
    cass_cond(fgets(row, 256, stream) != NULL);

    nrow++;
    while (fgets(row, 256, stream)) {
        printf("Line num: %u\n", nrow);
        nrow++;

        struct line line = parse_line(row);
        if (line.L == 1)
            test_st1201_uint8(line);
        else if (line.L == 2)
            test_st1201_uint16(line);
        else if (line.L == 4)
            test_st1201_uint32(line);
        else if (line.L == 8)
            test_st1201_uint64(line);
    }

    fclose(stream);
    return cass_status();
}

static void test_st1201_uint8(struct line line)
{
    struct st1201_uint8 st1201;
    cass_cond(st1201_init_uint8(line.a, line.b, &st1201) == 0);
    cass_close(st1201.impl.a, line.a);
    cass_close(st1201.impl.b, line.b);
    cass_close(st1201.impl.S_f, line.S_f);
    cass_close(st1201.impl.S_r, line.S_r);
    cass_close(st1201.impl.Z_o, line.Z_o);
    cass_equal_uint8(st1201_to_uint8(&st1201, line.x), line.y);
    cass_close(st1201_from_uint8(&st1201, line.y), line.x_r);
}

static void test_st1201_uint16(struct line line)
{
    struct st1201_uint16 st1201;
    cass_cond(st1201_init_uint16(line.a, line.b, &st1201) == 0);
    cass_close(st1201.impl.a, line.a);
    cass_close(st1201.impl.b, line.b);
    cass_close(st1201.impl.S_f, line.S_f);
    cass_close(st1201.impl.S_r, line.S_r);
    cass_close(st1201.impl.Z_o, line.Z_o);
    cass_equal_uint16(st1201_to_uint16(&st1201, line.x), line.y);
    cass_close(st1201_from_uint16(&st1201, line.y), line.x_r);
}

static void test_st1201_uint32(struct line line)
{
    struct st1201_uint32 st1201;
    cass_cond(st1201_init_uint32(line.a, line.b, &st1201) == 0);
    cass_close(st1201.impl.a, line.a);
    cass_close(st1201.impl.b, line.b);
    cass_close(st1201.impl.S_f, line.S_f);
    cass_close(st1201.impl.S_r, line.S_r);
    cass_close(st1201.impl.Z_o, line.Z_o);
    cass_equal_uint32(st1201_to_uint32(&st1201, line.x), line.y);
    cass_close(st1201_from_uint32(&st1201, line.y), line.x_r);
}

static void test_st1201_uint64(struct line line)
{
    struct st1201_uint64 st1201;
    cass_cond(st1201_init_uint64(line.a, line.b, &st1201) == 0);
    cass_close(st1201.impl.a, line.a);
    cass_close(st1201.impl.b, line.b);
    cass_close(st1201.impl.S_f, line.S_f);
    cass_close(st1201.impl.S_r, line.S_r);
    cass_close(st1201.impl.Z_o, line.Z_o);
    cass_equal_uint64(st1201_to_uint64(&st1201, line.x), line.y);
    cass_close(st1201_from_uint64(&st1201, line.y), line.x_r);
}