#ifndef LOGADDEXP_H
#define LOGADDEXP_H

#define LOGADDEXP_VERSION_MAJOR 1
#define LOGADDEXP_VERSION_MINOR 0
#define LOGADDEXP_VERSION_PATCH 3

#define LOGADDEXP_VERSION "1.0.3"

/* For Windows. */
#define _USE_MATH_DEFINES

#include <float.h>
#include <math.h>

/* Implements log(e^x + e^y).
 */
inline static double logaddexp(double const x, double const y)
{
    double const tmp = x - y;

    if (x == y)
        return x + M_LN2;

    if (tmp > 0)
        return x + log1p(exp(-tmp));
    else if (tmp <= 0)
        return y + log1p(exp(tmp));

    return tmp;
}

/* Implements log(sx * e^x + sy * e^y).
 *
 * Note: It assumes that sx * e^x + sy * e^y > 0.
 */
inline static double logaddexps(double const x, double const y, double const sx,
                                double const sy)
{
    double const tmp = x - y;

    double const sxx = log(fabs(sx)) + x;
    double const syy = log(fabs(sy)) + y;

    if (sxx == syy) {
        if (sx * sy > 0)
            return sxx + M_LN2;
        return -DBL_MAX;
    }

    if (sx > 0 && sy > 0) {
        if (tmp > 0)
            return sxx + log1p((sy / sx) * exp(-tmp));
        else if (tmp <= 0)
            return syy + log1p((sx / sy) * exp(tmp));
    } else if (sx > 0)
        return sxx + log1p((sy / sx) * exp(-tmp));
    else
        return syy + log1p((sx / sy) * exp(tmp));
    return tmp;
}

/* Returns log(|c|) and c/|c|, for c = sx * e^x + sy * e^y.
 */
inline static double logaddexpss(double const x, double const y, double sx, double sy,
                                 double *sign)
{
    double const sxx = log(fabs(sx)) + x;
    double const syy = log(fabs(sy)) + y;

    if (sxx == syy) {
        if (sx * sy > 0) {
            if (sx > 0)
                *sign = +1.0;
            else
                *sign = -1.0;
            return sxx + M_LN2;
        } else {
            *sign = 1.0;
            return -DBL_MAX;
        }
    }

    if (sxx > syy) {
        if (sx >= 0.0)
            *sign = +1.0;
        else
            *sign = -1.0;
    } else {
        if (sy >= 0.0)
            *sign = +1.0;
        else
            *sign = -1.0;
    }

    sx *= *sign;
    sy *= *sign;
    return logaddexps(x, y, sx, sy);
}

#endif
