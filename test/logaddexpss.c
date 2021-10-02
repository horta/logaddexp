#include "logaddexp/logaddexp.h"
#include <stddef.h>

#define EPSILON 1e-12

int test_logaddexpss_values(void);
int test_logaddexpss_dbl_max(void);
int test_logaddexpss_range_pos(void);
int test_logaddexpss_range_neg(void);
int test_logaddexpss_hand_made(void);

int main(void)
{
    if (test_logaddexpss_values())
        return 1;

    if (test_logaddexpss_dbl_max())
        return 1;

    if (test_logaddexpss_range_pos())
        return 1;

    if (test_logaddexpss_range_neg())
        return 1;

    if (test_logaddexpss_hand_made())
        return 1;

    return 0;
}

int test_logaddexpss_values(void)
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
        double v = logaddexpss(log(x[i]), log(y[i]), sx[i], sy[i], &sign);
        if (fabs(expected_val - v) > EPSILON)
            return 1;
        if (expected_sign != sign)
            return 1;
    }

    return 0;
}

int test_logaddexpss_dbl_max(void)
{
    double sign = 0.0;

    if (fabs(-DBL_MAX - logaddexpss(1, 1, 1, -1, &sign)) > EPSILON)
        return 1;

    if (1 != sign)
        return 1;

    return 0;
}

int test_logaddexpss_range_pos(void)
{

    double x[] = {1000000, -1000000, 1000200, -1000200};
    double y[] = {1000200, -1000200, 1000000, -1000000};
    double z[] = {1000200, -1000000, 1000200, -1000000};
    double signs[] = {1, 1, 1, 1};

    double sign = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        if (fabs(z[i] - logaddexpss(x[i], y[i], 1, 1, &sign)) > EPSILON)
            return 1;
        if (signs[i] != sign)
            return 1;
    }
    return 0;
}

int test_logaddexpss_range_neg(void)
{

    double x[] = {1000000, -1000000, 1000200, -1000200};
    double y[] = {1000200, -1000200, 1000000, -1000000};
    double z[] = {1000200, -1000000, 1000200, -1000000};
    double signs[] = {-1, 1, 1, -1};

    double sign = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        if (fabs(z[i] - logaddexpss(x[i], y[i], 1, -1, &sign)) > EPSILON)
            return 1;
        if (signs[i] != sign)
            return 1;
    }
    return 0;
}

int test_logaddexpss_hand_made(void)
{
    double expected = 2.9946394843421738;
    double sign = 0.0;

    if (fabs(expected - logaddexpss(-39.1, 3.1, -3.3, 0.9, &sign)) > EPSILON)
        return 1;

    if (sign != 1)
        return 1;

    if (fabs(expected - logaddexpss(-39.1, 3.1, -3.3, -0.9, &sign)) > EPSILON)
        return 1;

    if (sign != -1)
        return 1;

    expected = -3.0440928402878482;
    if (fabs(expected - logaddexpss(-4., -5., -3.3, 1.9, &sign)) > EPSILON)
        return 1;

    if (sign != -1)
        return 1;

    return 0;
}
