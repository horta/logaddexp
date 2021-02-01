#include "logaddexp/logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-12

int test_logaddexpg_values(void);
int test_logaddexpg_dbl_max(void);
int test_logaddexpg_range_pos(void);
int test_logaddexpg_range_neg(void);
int test_logaddexpg_hand_made(void);

int main()
{
    if (test_logaddexpg_values())
        return 1;

    if (test_logaddexpg_dbl_max())
        return 1;

    if (test_logaddexpg_range_pos())
        return 1;

    if (test_logaddexpg_range_neg())
        return 1;

    if (test_logaddexpg_hand_made())
        return 1;

    return 0;
}

int test_logaddexpg_values(void)
{
    double x[] = {1, 2, 3, 4, 5};
    double y[] = {5, 4, 3, 2, 1};
    double sx[] = {1, 2, 3, 4, 5};
    double sy[] = {-1, -1.5, 0, 1.5, 1};

    for (size_t i = 0; i < 5; ++i) {
        double c = sx[i] * x[i] + sy[i] * y[i];
        double expected_val = log(fabs(c));
        double expected_sign = c / fabs(c);
        double sign = 0.0;
        double v = logaddexpgd(log(x[i]), log(y[i]), sx[i], sy[i], &sign);
        if (fabs(expected_val - v) > EPSILON)
            return 1;
        if (expected_sign != sign)
            return 1;
    }

    return 0;
}

int test_logaddexpg_dbl_max(void)
{
    double sign = 0.0;

    if (fabs(-DBL_MAX - logaddexpgd(1., 1., 1., -1., &sign)) > EPSILON)
        return 1;

    if (1 != sign)
        return 1;

    return 0;
}

int test_logaddexpg_range_pos(void)
{

    double x[] = {1000000, -1000000, 1000200, -1000200};
    double y[] = {1000200, -1000200, 1000000, -1000000};
    double z[] = {1000200, -1000000, 1000200, -1000000};
    double signs[] = {1, 1, 1, 1};

    double sign = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        if (fabs(z[i] - logaddexpgd(x[i], y[i], 1., 1., &sign)) > EPSILON)
            return 1;
        if (signs[i] != sign)
            return 1;
    }
    return 0;
}

int test_logaddexpg_range_neg(void)
{

    double x[] = {1000000, -1000000, 1000200, -1000200};
    double y[] = {1000200, -1000200, 1000000, -1000000};
    double z[] = {1000200, -1000000, 1000200, -1000000};
    double signs[] = {-1, 1, 1, -1};

    double sign = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        if (fabs(z[i] - logaddexpgd(x[i], y[i], 1., -1., &sign)) > EPSILON)
            return 1;
        if (signs[i] != sign)
            return 1;
    }
    return 0;
}

int test_logaddexpg_hand_made(void)
{
    double expected = 2.9946394843421738;
    double sign = 0.0;

    if (fabs(expected - logaddexpgd(-39.1, 3.1, -3.3, 0.9, &sign)) > EPSILON)
        return 1;

    if (sign != 1)
        return 1;

    if (fabs(expected - logaddexpgd(-39.1, 3.1, -3.3, -0.9, &sign)) > EPSILON)
        return 1;

    if (sign != -1)
        return 1;

    expected = -3.0440928402878482;
    if (fabs(expected - logaddexpgd(-4., -5., -3.3, 1.9, &sign)) > EPSILON)
        return 1;

    if (sign != -1)
        return 1;

    return 0;
}
