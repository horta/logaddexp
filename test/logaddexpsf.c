#include "logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-6

int test_logaddexpsf_values(void);
int test_logaddexpsf_flt_max(void);
int test_logaddexpsf_range(void);
int test_logaddexpsf_hand_made(void);

int main()
{
    if (test_logaddexpsf_values())
        return 1;

    if (test_logaddexpsf_flt_max())
        return 1;

    if (test_logaddexpsf_range())
        return 1;

    if (test_logaddexpsf_hand_made())
        return 1;

    return 0;
}

int test_logaddexpsf_values(void)
{
    float x[] = {1, 2, 3, 4, 5};
    float y[] = {5, 4, 3, 2, 1};
    float sx[] = {1, 2, 3, 4, 5};
    float sy[] = {-1, -1.5, 0, 1.5, 1};

    for (size_t i = 0; i < 5; ++i) {
        float expected = logf(sx[i] * x[i] + sy[i] * y[i]);
        float v = logaddexpsf(logf(x[i]), logf(y[i]), sx[i], sy[i]);
        if (fabsf(expected - v) > EPSILON)
            return 1;
    }

    return 0;
}

int test_logaddexpsf_flt_max(void)
{
    if (fabsf(-FLT_MAX - logaddexpsf(1, 1, 1, -1)) > EPSILON)
        return 1;

    float v = logaddexpsf(1, 1, 1, -1);
    if (fabsf(1 - logaddexpsf(v, 1, 1, 1)) > EPSILON)
        return 1;

    return 0;
}

int test_logaddexpsf_range(void)
{

    float x[] = {1000000, -1000000, 1000200, -1000200};
    float y[] = {1000200, -1000200, 1000000, -1000000};
    float z[] = {1000200, -1000000, 1000200, -1000000};

    for (size_t i = 0; i < 4; ++i) {
        if (fabsf(z[i] - logaddexpsf(x[i], y[i], 1, 1)) > EPSILON)
            return 1;
    }
    return 0;
}

int test_logaddexpsf_hand_made(void)
{
    float expected = 2.9946394843421738;

    if (fabsf(expected - logaddexpsf(-39.1, 3.1, -3.3, 0.9)) > EPSILON)
        return 1;

    expected = -7.470820903793559;
    if (fabsf(expected - logaddexpsf(-4., -5., -0.3, 0.9)) > EPSILON)
        return 1;

    return 0;
}
