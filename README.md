# logaddexp

C library that implements the logarithm of the sum of exponentiations.

Inspired by NumPy's `logaddexp` function, I have implemented the
following functions in C:

```c
/* Computes ㏒ₑ(𝑒ˣ + 𝑒ʸ) in safe and accurate way.
 *
 * For example, `log(exp(1e3) + exp(-INFINITY))` will likely overflow,
 * while `logaddexp(1e3, -INFINITY)` will return `1e3`.
 */
double logaddexp(double x, double y);

/* Computes ㏒ₑ(𝑠ₓ⋅𝑒ˣ + 𝑠ᵧ⋅𝑒ʸ) in safe and accurate way.
 *
 * It is a weighted version of `logaddexp`, assuming that
 * 𝑠ₓ⋅𝑒ˣ + 𝑠ᵧ⋅𝑒ʸ > 0.
 */
double logaddexps(double x, double y, double sx, double sy);

/* Computes ㏒ₑ(|𝑐|) and 𝑐/|𝑐|, for 𝑐 = 𝑠ₓ⋅𝑒ˣ + 𝑠ᵧ⋅𝑒ʸ.
 *
 * It is a generalisation of `logaddexps`.
 */
double logaddexpg(double x, double y, double sx, double sy, double *sign);
```

# How to use?

## Easiest way

Include `logaddexp.h` in your C/C++ project.

## CMake way

In your `CMakeLists.txt`, add the following:

```
find_package(logaddexp REQUIRED)

target_link_libraries(mylib PRIVATE LOGADDEXP::logaddexp)
```
