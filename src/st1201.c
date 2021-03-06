/* For Windows. */
#define _USE_MATH_DEFINES

#include "st1201/st1201.h"
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t const POSITIVE_INFINITY_HIGH_BYTE = 0xC8;
static uint8_t const NEGATIVE_INFINITY_HIGH_BYTE = 0xE8;
static uint8_t const POSITIVE_QUIET_NAN_HIGH_BYTE = 0xD0;
static uint8_t const NEGATIVE_QUIET_NAN_HIGH_BYTE = 0xF0;
static uint8_t const HIGH_BITS_MASK = 0xF8;

inline static int st1201_init(double a, double b, unsigned nbytes,
                              struct st1201 *st1201);

#define ST1201_MAKE_INIT_TYPE_FUNC(B)                                                  \
    int st1201_init_uint##B(double a, double b, struct st1201_uint##B *st1201)         \
    {                                                                                  \
        return st1201_init(a, b, B / 8, &st1201->impl);                                \
    }

ST1201_MAKE_INIT_TYPE_FUNC(8)
ST1201_MAKE_INIT_TYPE_FUNC(16)
ST1201_MAKE_INIT_TYPE_FUNC(32)
ST1201_MAKE_INIT_TYPE_FUNC(64)

#define ST1201_MAKE_TO_TYPE_FUNC(B)                                                    \
    uint##B##_t st1201_to_uint##B(struct st1201_uint##B *st1201, double x)             \
    {                                                                                  \
        unsigned const nshifts = B - 8;                                                \
        if (x == +INFINITY)                                                            \
            return ((uint##B##_t)POSITIVE_INFINITY_HIGH_BYTE) << nshifts;              \
        else if (x == -INFINITY)                                                       \
            return ((uint##B##_t)NEGATIVE_INFINITY_HIGH_BYTE) << nshifts;              \
        else if (isnan(x)) {                                                           \
            if (signbit(x))                                                            \
                return ((uint##B##_t)NEGATIVE_QUIET_NAN_HIGH_BYTE) << nshifts;         \
            else                                                                       \
                return ((uint##B##_t)POSITIVE_QUIET_NAN_HIGH_BYTE) << nshifts;         \
        }                                                                              \
        if (x < st1201->impl.a || st1201->impl.b < x)                                  \
            return ((uint##B##_t)NEGATIVE_QUIET_NAN_HIGH_BYTE) << nshifts;             \
                                                                                       \
        return (uint##B##_t)(st1201->impl.S_f * (x - st1201->impl.a) +                 \
                             st1201->impl.Z_o);                                        \
    }

ST1201_MAKE_TO_TYPE_FUNC(8)
ST1201_MAKE_TO_TYPE_FUNC(16)
ST1201_MAKE_TO_TYPE_FUNC(32)
ST1201_MAKE_TO_TYPE_FUNC(64)

#define ST1201_MAKE_FROM_TYPE_NORMAL_FUNC(B)                                           \
    inline static double _st1201_from_uint##B##_normal(struct st1201_uint##B *st1201,  \
                                                       uint##B##_t y)                  \
    {                                                                                  \
        return st1201->impl.S_r * ((double)y - st1201->impl.Z_o) + st1201->impl.a;     \
    }

ST1201_MAKE_FROM_TYPE_NORMAL_FUNC(8)
ST1201_MAKE_FROM_TYPE_NORMAL_FUNC(16)
ST1201_MAKE_FROM_TYPE_NORMAL_FUNC(32)
ST1201_MAKE_FROM_TYPE_NORMAL_FUNC(64)

#define ST1201_MAKE_FROM_TYPE_FUNC(B)                                                  \
    double st1201_from_uint##B(struct st1201_uint##B *st1201, uint##B##_t y)           \
    {                                                                                  \
        unsigned const nshifts = B - 8;                                                \
        uint8_t high_bits = (uint8_t)(y >> nshifts);                                   \
                                                                                       \
        if ((high_bits & 0x80) == 0x00) {                                              \
            return _st1201_from_uint##B##_normal(st1201, y);                           \
        } else if (y == ((uint##B##_t)0x80) << nshifts) {                              \
            return _st1201_from_uint##B##_normal(st1201, y);                           \
        }                                                                              \
                                                                                       \
        high_bits &= HIGH_BITS_MASK;                                                   \
        if (high_bits == POSITIVE_INFINITY_HIGH_BYTE)                                  \
            return +INFINITY;                                                          \
        else if (high_bits == NEGATIVE_INFINITY_HIGH_BYTE)                             \
            return -INFINITY;                                                          \
        return NAN;                                                                    \
    }

ST1201_MAKE_FROM_TYPE_FUNC(8)
ST1201_MAKE_FROM_TYPE_FUNC(16)
ST1201_MAKE_FROM_TYPE_FUNC(32)
ST1201_MAKE_FROM_TYPE_FUNC(64)

inline static int st1201_init(double a, double b, unsigned nbytes,
                              struct st1201 *st1201)
{
    unsigned const L = nbytes;
    double const b_pow = ceil(log2(b - a));
    double const d_pow = 8 * L - 1;

    st1201->a = a;
    st1201->b = b;

    st1201->S_f = pow(2.0, d_pow - b_pow);
    st1201->S_r = pow(2.0, b_pow - d_pow);

    if (a < 0 && b > 0)
        st1201->Z_o = st1201->S_f * a - floor(st1201->S_f * a);
    else
        st1201->Z_o = 0.0;

    return 0;
}
