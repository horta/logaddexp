#include "logaddexp/logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-6

int test_logaddexpgf_values(void);
int test_logaddexpgf_flt_max(void);
int test_logaddexpgf_range_pos(void);
int test_logaddexpgf_range_neg(void);
int test_logaddexpgf_hand_made(void);

int main()
{
    if (test_logaddexpgf_values())
        return 1;

    if (test_logaddexpgf_flt_max())
        return 1;

    if (test_logaddexpgf_range_pos())
        return 1;

    if (test_logaddexpgf_range_neg())
        return 1;

    if (test_logaddexpgf_hand_made())
        return 1;

    return 0;
}

int test_logaddexpgf_values(void)
{
    float x[] = {1, 2, 3, 4, 5};
    float y[] = {5, 4, 3, 2, 1};
    float sx[] = {1, 2, 3, 4, 5};
    float sy[] = {-1, -1.5, 0, 1.5, 1};

    for (size_t i = 0; i < 5; ++i) {
        float c = sx[i] * x[i] + sy[i] * y[i];
        float expected_val = logf(fabsf(c));
        float expected_sign = c / fabsf(c);
        float sign = 0.0;
        float v = logaddexpgf(logf(x[i]), logf(y[i]), sx[i], sy[i], &sign);
        if (fabsf(expected_val - v) > EPSILON)
            return 1;
        if (expected_sign != sign)
            return 1;
    }

    return 0;
}

int test_logaddexpgf_flt_max(void)
{
    float sign = 0.0;

    if (fabsf(-FLT_MAX - logaddexpgf(1, 1, 1, -1, &sign)) > EPSILON)
        return 1;

    if (1 != sign)
        return 1;

    return 0;
}

int test_logaddexpgf_range_pos(void)
{

    float x[] = {1000000, -1000000, 1000200, -1000200};
    float y[] = {1000200, -1000200, 1000000, -1000000};
    float z[] = {1000200, -1000000, 1000200, -1000000};
    float signs[] = {1, 1, 1, 1};

    float sign = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        if (fabsf(z[i] - logaddexpgf(x[i], y[i], 1, 1, &sign)) > EPSILON)
            return 1;
        if (signs[i] != sign)
            return 1;
    }
    return 0;
}

int test_logaddexpgf_range_neg(void)
{

    float x[] = {1000000, -1000000, 1000200, -1000200};
    float y[] = {1000200, -1000200, 1000000, -1000000};
    float z[] = {1000200, -1000000, 1000200, -1000000};
    float signs[] = {-1, 1, 1, -1};

    float sign = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        if (fabsf(z[i] - logaddexpgf(x[i], y[i], 1, -1, &sign)) > EPSILON)
            return 1;
        if (signs[i] != sign)
            return 1;
    }
    return 0;
}

int test_logaddexpgf_hand_made(void)
{
    float expected = 2.9946394843421738;
    float sign = 0.0;

    if (fabsf(expected - logaddexpgf(-39.1, 3.1, -3.3, 0.9, &sign)) > EPSILON)
        return 1;

    if (sign != 1)
        return 1;

    if (fabsf(expected - logaddexpgf(-39.1, 3.1, -3.3, -0.9, &sign)) > EPSILON)
        return 1;

    if (sign != -1)
        return 1;

    expected = -3.0440928402878482;
    if (fabsf(expected - logaddexpgf(-4., -5., -3.3, 1.9, &sign)) > EPSILON)
        return 1;

    if (sign != -1)
        return 1;

    return 0;
}
