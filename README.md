# logaddexp

C library that implements the logarithm of the sum of exponentiations.

Inspired by NumPy's `logaddexp` function, I have implemented the
following functions in C:

```c
/* Computes ㏒ₑ(𝑒ˣ + 𝑒ʸ) in a safe and accurate way.
 *
 * For example, `log(exp(1e3) + exp(-INFINITY))` will likely overflow,
 * while `logaddexp(1e3, -INFINITY)` will return `1e3`.
 */
double logaddexp(double x, double y);
float logaddexpf(float x, float y);

/* Computes ㏒ₑ(𝑠ₓ⋅𝑒ˣ + 𝑠ᵧ⋅𝑒ʸ) in a safe and accurate way.
 *
 * It is a weighted version of `logaddexp`, assuming that
 * 𝑠ₓ⋅𝑒ˣ + 𝑠ᵧ⋅𝑒ʸ > 0.
 */
double logaddexps(double x, double y, double sx, double sy);
float logaddexpsf(float x, float y, float sx, float sy);

/* Computes ㏒ₑ(|𝑐|) and 𝑐/|𝑐|, for 𝑐 = 𝑠ₓ⋅𝑒ˣ + 𝑠ᵧ⋅𝑒ʸ.
 *
 * It is a generalisation of `logaddexps`.
 */
double logaddexpg(double x, double y, double sx, double sy, double *sign);
float logaddexpgf(float x, float y, float sx, float sy, float *sign);
```

# How to use?

## Easiest way

Include the `include/logaddexp/logaddexp.h` file in your C/C++ project.

## CMake way

In your `CMakeLists.txt`, add the following:

```
find_package(logaddexp REQUIRED)

target_link_libraries(mylib PRIVATE LOGADDEXP::logaddexp)
```

Then add `#include "logaddexp/logaddexp.h"` in your source files.

# Install

Enter the following command in your terminal:

```bash
/bin/bash -c "$(curl -fsSL https://git.io/Jz7Oa)" -s horta/logaddexp
```

## Authors

* [Danilo Horta](https://github.com/horta)

## License

This project is licensed under the [MIT License](https://raw.githubusercontent.com/horta/logaddexp/master/LICENSE.md).
