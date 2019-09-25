![Travis (.com)](https://img.shields.io/travis/com/horta/logaddexp?label=linux%2Fmacos)

# logaddexp

C library that implements the logarithm of the sum of exponentiations.

Inspired by NumPy's `logaddexp` function, I have implemented the
following functions in C:

```c
/* Implements log(e^x + e^y).
 */
double logaddexp(double x, double y);

/* Implements log(sx * e^x + sy * e^y).
 *
 * It assumes that sx * e^x + sy * e^y > 0.
 */
double logaddexps(double x, double y, double sx, double sy);

/* Returns log(|c|) and c/|c|, for c = sx * e^x + sy * e^y.
 */
double logaddexpss(double x, double y, double sx, double sy, double* sign);
```

# How to use?

Include `logaddexp.h` in your C/C++ project.
