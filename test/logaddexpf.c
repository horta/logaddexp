#include "logaddexp/logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-6f

int test_logaddexpf_values(void);
int test_logaddexpf_range(void);
int test_logaddexpf_inf(void);
int test_logaddexpf_nan(void);

int main(void)
{
    if (test_logaddexpf_values()) return 1;

    if (test_logaddexpf_range()) return 1;

    if (test_logaddexpf_inf()) return 1;

    if (test_logaddexpf_nan()) return 1;

    return 0;
}

int test_logaddexpf_values(void)
{
    float x[] = {1, 2, 3, 4, 5};
    float y[] = {5, 4, 3, 2, 1};
    float z[] = {6, 6, 6, 6, 6};

    for (size_t i = 0; i < 5; ++i)
    {
        if (fabsf(logf(z[i]) - logaddexpf(logf(x[i]), logf(y[i]))) > EPSILON)
            return 1;
    }
    return 0;
}

int test_logaddexpf_range(void)
{
    float x[] = {1000000, -1000000, 1000200, -1000200};
    float y[] = {1000200, -1000200, 1000000, -1000000};
    float z[] = {1000200, -1000000, 1000200, -1000000};

    for (size_t i = 0; i < 4; ++i)
    {
        if (fabsf(z[i] - logaddexpf(x[i], y[i])) > EPSILON) return 1;
    }
    return 0;
}

int test_logaddexpf_inf(void)
{
    float x[] = {INFINITY, -INFINITY, INFINITY,  -INFINITY,
                 INFINITY, 1,         -INFINITY, 1};
    float y[] = {INFINITY, INFINITY, -INFINITY, -INFINITY,
                 1,        INFINITY, 1,         -INFINITY};
    float z[] = {INFINITY, INFINITY, INFINITY, -INFINITY,
                 INFINITY, INFINITY, 1,        1};

    for (size_t i = 0; i < 8; ++i)
    {
        if (logaddexpf(x[i], y[i]) != z[i]) return 1;
    }
    return 0;
}

int test_logaddexpf_nan(void)
{
    if (!isnan(logaddexpf(NAN, INFINITY))) return 1;

    if (!isnan(logaddexpf(INFINITY, NAN))) return 1;

    if (!isnan(logaddexpf(NAN, 0))) return 1;

    if (!isnan(logaddexpf(0, NAN))) return 1;

    if (!isnan(logaddexpf(NAN, NAN))) return 1;

    return 0;
}
