#ifndef ST1201_H
#define ST1201_H

#define ST1201_VERSION_MAJOR 1
#define ST1201_VERSION_MINOR 0
#define ST1201_VERSION_PATCH 0

#define ST1201_VERSION "1.0.0"

/* For Windows. */
#define _USE_MATH_DEFINES

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
/* #include <stdlib.h> */

static uint8_t const POSITIVE_INFINITY_HIGH_BYTE = 0xC8;
static uint8_t const NEGATIVE_INFINITY_HIGH_BYTE = 0xE8;
static uint8_t const POSITIVE_QUIET_NAN_HIGH_BYTE = 0xD0;
static uint8_t const NEGATIVE_QUIET_NAN_HIGH_BYTE = 0xF0;
static uint8_t const POSITIVE_SIGNAL_NAN_HIGH_BYTE = 0xD8;
static uint8_t const NEGATIVE_SIGNAL_NAN_HIGH_BYTE = 0xF8;

struct st1201_uint8
{
    double a;   /** Left bound on the floating-point */
    double S_f; /** Scaling for forward mapping */
    double S_r; /** Scaling for reverse mapping */
    double Z_o; /** Zero offset */
};

struct st1201_uint16
{
    double a;   /** Left bound on the floating-point */
    double S_f; /** Scaling for forward mapping */
    double S_r; /** Scaling for reverse mapping */
    double Z_o; /** Zero offset */
};

struct st1201_uint32
{
    double a;   /** Left bound on the floating-point */
    double S_f; /** Scaling for forward mapping */
    double S_r; /** Scaling for reverse mapping */
    double Z_o; /** Zero offset */
};

struct st1201_uint64
{
    double a;   /** Left bound on the floating-point */
    double S_f; /** Scaling for forward mapping */
    double S_r; /** Scaling for reverse mapping */
    double Z_o; /** Zero offset */
};

#if defined(HAVE_ATTR_FORMAT)
#define ATTR_FORMAT __attribute__((format(printf, 1, 2)))
#else
#define ATTR_FORMAT
#endif

inline static void st1201_error(char const *err, ...)
{
    va_list params;
    va_start(params, err);
    vfprintf(stderr, err, params);
    fputc('\n', stderr);
    va_end(params);
}

/* static inline void st1201_die(char const *err, ...) */
/* { */
/*     va_list params; */
/*     va_start(params, err); */
/*     st1201_error(err, params); */
/*     va_end(params); */
/*     exit(1); */
/* } */

inline static int st1201_init_uint8(double a, double b, unsigned nbytes,
                                    struct st1201_uint8 *st1201)
{
    unsigned const L = nbytes;

    double const b_pow_tmp = ceil(log2(b - a));
    if (b_pow_tmp > UINT_MAX) {
        st1201_error("b_pow overflow");
        return 1;
    }
    unsigned const b_pow = (unsigned)b_pow_tmp;

    if (8 * L - 1 > UINT_MAX) {
        st1201_error("d_pow overflow");
        return 1;
    }
    unsigned const d_pow = (unsigned)(8 * L - 1);

    st1201->a = a;
    if (d_pow >= b_pow) {
        st1201->S_f = (double)(1 << (d_pow - b_pow));
        st1201->S_r = 1.0 / st1201->S_f;
    } else {
        st1201->S_r = (double)(1 << (b_pow - d_pow));
        st1201->S_f = 1.0 / st1201->S_r;
    }

    if (a < 0 && b > 0)
        st1201->Z_o = st1201->S_f * a - floor(st1201->S_f * a);
    else
        st1201->Z_o = 0.0;

    return 0;
}

/* inline static int st1201_init_precision(double left, double right, double prec, */
/*                                         struct st1201 *st1201) */
/* { */
/*     double const a = left; */
/*     double const b = right; */
/*     double const g = prec; */
/*     double const L_bits = ceil(log2(b - a)) - floor(log2(g)) + 1; */
/*     double const L_tmp = ceil(L_bits / 8.0); */

/*     if (L_tmp > UINT_MAX) { */
/*         st1201_error("L overflow"); */
/*         return 1; */
/*     } */
/*     if (L_tmp < 1.0) { */
/*         st1201_error("L must be positive"); */
/*         return 1; */
/*     } */
/*     unsigned const L = (unsigned)L_tmp; */
/*     return st1201_init(a, b, L, st1201); */
/* } */

/* inline static uint32_t st1201_to_uint32(struct st1201 *st1201, double x) */
/* { */
/*     return (uint32_t)(st1201->S_f * (x - st1201->a) + st1201->Z_o); */
/* } */

/* inline static double st1201_from_uint32(struct st1201 *st1201, uint32_t y) */
/* { */
/*     return st1201->S_r * (y - st1201->Z_o) + st1201->a; */
/* } */

/* inline static int32_t st1201_to_int32(struct st1201 *st1201, double x) */
/* { */
/*     return (int32_t)(st1201->S_f * (x - st1201->a) + st1201->Z_o); */
/* } */

/* inline static double st1201_from_int32(struct st1201 *st1201, int32_t y) */
/* { */
/*     return st1201->S_r * (y - st1201->Z_o) + st1201->a; */
/* } */

/* inline static uint16_t st1201_to_uint16(struct st1201 *st1201, double x) */
/* { */
/*     return (uint16_t)(st1201->S_f * (x - st1201->a) + st1201->Z_o); */
/* } */

/* inline static double st1201_from_uint16(struct st1201 *st1201, uint16_t y) */
/* { */
/*     return st1201->S_r * (y - st1201->Z_o) + st1201->a; */
/* } */

/* inline static int16_t st1201_to_int16(struct st1201 *st1201, double x) */
/* { */
/*     return (int16_t)(st1201->S_f * (x - st1201->a) + st1201->Z_o); */
/* } */

/* inline static double st1201_from_int16(struct st1201 *st1201, int16_t y) */
/* { */
/*     return st1201->S_r * (y - st1201->Z_o) + st1201->a; */
/* } */

inline static uint8_t st1201_to_uint8(struct st1201_uint8 *st1201, double x)
{
    if (x == +INFINITY)
        return POSITIVE_INFINITY_HIGH_BYTE;
    else if (x == -INFINITY)
        return NEGATIVE_INFINITY_HIGH_BYTE;
    return (uint8_t)(st1201->S_f * (x - st1201->a) + st1201->Z_o);
}

inline static double st1201_from_uint8(struct st1201_uint8 *st1201, uint8_t y)
{
    return st1201->S_r * (y - st1201->Z_o) + st1201->a;
}

#endif
