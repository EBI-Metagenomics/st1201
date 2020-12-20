#ifndef ST1201_H
#define ST1201_H

#include <stdint.h>

#define ST1201_VERSION_MAJOR 1
#define ST1201_VERSION_MINOR 0
#define ST1201_VERSION_PATCH 1

#define ST1201_VERSION "1.0.1"

struct st1201
{
    double a;   /** Left bound on the floating-point */
    double b;   /** Right bound on the floating-point */
    double S_f; /** Scaling for forward mapping */
    double S_r; /** Scaling for reverse mapping */
    double Z_o; /** Zero offset */
};

struct st1201_uint8
{
    struct st1201 impl;
};

struct st1201_uint16
{
    struct st1201 impl;
};

struct st1201_uint32
{
    struct st1201 impl;
};

struct st1201_uint64
{
    struct st1201 impl;
};

int st1201_init_uint8(double a, double b, struct st1201_uint8 *st1201);
int st1201_init_uint16(double a, double b, struct st1201_uint16 *st1201);
int st1201_init_uint32(double a, double b, struct st1201_uint32 *st1201);
int st1201_init_uint64(double a, double b, struct st1201_uint64 *st1201);

uint8_t st1201_to_uint8(struct st1201_uint8 *st1201, double x);
uint16_t st1201_to_uint16(struct st1201_uint16 *st1201, double x);
uint32_t st1201_to_uint32(struct st1201_uint32 *st1201, double x);
uint64_t st1201_to_uint64(struct st1201_uint64 *st1201, double x);

double st1201_from_uint8(struct st1201_uint8 *st1201, uint8_t y);
double st1201_from_uint16(struct st1201_uint16 *st1201, uint16_t y);
double st1201_from_uint32(struct st1201_uint32 *st1201, uint32_t y);
double st1201_from_uint64(struct st1201_uint64 *st1201, uint64_t y);

#endif
