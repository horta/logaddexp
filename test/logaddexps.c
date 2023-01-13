#include "logaddexp/logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-12

int test_logaddexps_values(void);
int test_logaddexps_dbl_max(void);
int test_logaddexps_range(void);
int test_logaddexps_hand_made(void);

int main(void)
{
    if (test_logaddexps_values()) return 1;

    if (test_logaddexps_dbl_max()) return 1;

    if (test_logaddexps_range()) return 1;

    if (test_logaddexps_hand_made()) return 1;

    return 0;
}

int test_logaddexps_values(void)
{
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {5, 4, 3, 2, 1};
    double sx[] = {1, 2, 3, 4, 5};
    double sy[] = {-1, -1.5, 0, 1.5, 1};

    for (size_t i = 0; i < 5; ++i)
    {
        double expected = log(sx[i] * x[i] + sy[i] * y[i]);
        double v = logaddexps(log(x[i]), log(y[i]), sx[i], sy[i]);
        if (fabs(expected - v) > EPSILON) return 1;
    }

    return 0;
}

int test_logaddexps_dbl_max(void)
{
    if (fabs(-DBL_MAX - logaddexps(1., 1., 1., -1.)) > EPSILON) return 1;

    double v = logaddexps(1., 1., 1., -1.);
    if (fabs(1 - logaddexps(v, 1., 1., 1.)) > EPSILON) return 1;

    return 0;
}

int test_logaddexps_range(void)
{

    double x[] = {1000000, -1000000, 1000200, -1000200};
    double y[] = {1000200, -1000200, 1000000, -1000000};
    double z[] = {1000200, -1000000, 1000200, -1000000};

    for (size_t i = 0; i < 4; ++i)
    {
        if (fabs(z[i] - logaddexps(x[i], y[i], 1., 1.)) > EPSILON) return 1;
    }
    return 0;
}

int test_logaddexps_hand_made(void)
{
    double expected = 2.9946394843421738;

    if (fabs(expected - logaddexps(-39.1, 3.1, -3.3, 0.9)) > EPSILON) return 1;

    expected = -7.470820903793559;
    if (fabs(expected - logaddexps(-4., -5., -0.3, 0.9)) > EPSILON) return 1;

    return 0;
}
