#include <omp.h>
#include "elapsed.h"
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

/* Implements log(e^x + e^y).
 */
inline static double logaddexp(double const x, double const y)
{
    double const tmp = x - y;

    /* if (x == y) */
    /*     return x + M_LN2; */

    return (tmp > 0) * x + (tmp <= 0) * y + log1p(exp(copysign(tmp, -1.0)));

    /* if (tmp > 0) */
    /*     return x + log1p(exp(-tmp)); */
    /* else if (tmp <= 0) */
    /*     return y + log1p(exp(tmp)); */

    return tmp;
}

static inline double arr_max(double const *arr, unsigned const len)
{
    double r = arr[0];
    for (size_t i = 1; i < len; ++i)
    {
      if (arr[i] > r)
	r = arr[i];
    }
    return r;
}

static inline double arr_min(double const *arr, unsigned len)
{
    double r = +INFINITY;
    for (size_t i = 0; i < len; ++i)
        r = fmin(r, arr[i]);
    return r;
}

static inline double logsumexp(double const *arr, unsigned len)
{
    double r = -DBL_MAX;
    for (size_t i = 0; i < len; ++i)
        r = logaddexp(r, arr[i]);
    return r;
}

static inline double logsumexp2(double const *arr, unsigned len)
{
    double const max = arr_max(arr, len);
    if (isinf(max) && max > 0.0)
        return +INFINITY;
    double sum = 0.0;
    /* printf("Max: %f\n", max); */
    for (size_t i = 0; i < len; ++i) {
        sum += exp(arr[i] - max);
    }
    return max + log(sum);
}

int main()
{
    double const rand_floats[] = {0.342, 1.2, -10.2, 9.12, 0.00001, 1.24, -DBL_MAX};
    /* double const rand_floats[] = {0.342, 1.2, -10.2, 9.12, 0.00001, 1.24, -INFINITY,
     * +INFINITY}; */

    unsigned const size = 1000 * 1000 * 100;
    double *arr = malloc(sizeof(double) * size);

    for (unsigned i = 0; i < size; ++i)
        arr[i] = rand_floats[i % ARRAY_SIZE(rand_floats)];

    struct elapsed *elapsed = elapsed_create();

    elapsed_start(elapsed);
    double const result = logsumexp(arr, size);
    /* double const result = logsumexp2(arr, size); */
    elapsed_end(elapsed);

    printf("Result: %.16f\n", result);
    if (fabs(result - 23.2931898785768858) > 1e-10)
        printf("EEEEEEEEERRRRRRRRRRRRRROOOOOOOOOOOOORRRR\n");
    printf("Elapsed: %.16f\n", elapsed_seconds(elapsed));

    elapsed_destroy(elapsed);
    free(arr);
    return 0;
}
