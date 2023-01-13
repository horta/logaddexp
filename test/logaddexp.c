#include "logaddexp/logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-12

int test_logaddexp_values(void);
int test_logaddexp_range(void);
int test_logaddexp_inf(void);
int test_logaddexp_nan(void);

int main(void)
{
    if (test_logaddexp_values()) return 1;

    if (test_logaddexp_range()) return 1;

    if (test_logaddexp_inf()) return 1;

    if (test_logaddexp_nan()) return 1;

    return 0;
}

int test_logaddexp_values(void)
{
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {5, 4, 3, 2, 1};
    double z[] = {6, 6, 6, 6, 6};

    for (size_t i = 0; i < 5; ++i)
    {
        if (fabs(log(z[i]) - logaddexp(log(x[i]), log(y[i]))) > EPSILON)
            return 1;
    }
    return 0;
}

int test_logaddexp_range(void)
{
    double x[] = {1000000, -1000000, 1000200, -1000200};
    double y[] = {1000200, -1000200, 1000000, -1000000};
    double z[] = {1000200, -1000000, 1000200, -1000000};

    for (size_t i = 0; i < 4; ++i)
    {
        if (fabs(z[i] - logaddexp(x[i], y[i])) > EPSILON) return 1;
    }
    return 0;
}

int test_logaddexp_inf(void)
{
    double x[] = {INFINITY, -INFINITY, INFINITY,  -INFINITY,
                  INFINITY, 1,         -INFINITY, 1};
    double y[] = {INFINITY, INFINITY, -INFINITY, -INFINITY,
                  1,        INFINITY, 1,         -INFINITY};
    double z[] = {INFINITY, INFINITY, INFINITY, -INFINITY,
                  INFINITY, INFINITY, 1,        1};

    for (size_t i = 0; i < 8; ++i)
    {
        if (logaddexp(x[i], y[i]) != z[i]) return 1;
    }
    return 0;
}

int test_logaddexp_nan(void)
{
    if (!isnan(logaddexp(NAN, INFINITY))) return 1;

    if (!isnan(logaddexp(INFINITY, NAN))) return 1;

    if (!isnan(logaddexp(NAN, 0))) return 1;

    if (!isnan(logaddexp(0., NAN))) return 1;

    if (!isnan(logaddexp(NAN, NAN))) return 1;

    return 0;
}
