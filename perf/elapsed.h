#ifndef ELAPSED_H
#define ELAPSED_H

#include <stdlib.h>
#include <time.h>

struct elapsed
{
    clock_t start;
    clock_t end;
};

static inline struct elapsed* elapsed_create(void) { return malloc(sizeof(struct elapsed)); }
static inline void            elapsed_destroy(struct elapsed* elapsed) { free(elapsed); }

static inline double elapsed_seconds(struct elapsed* elapsed)
{
    return ((double)(elapsed->end - elapsed->start)) / CLOCKS_PER_SEC;
}

static inline void   elapsed_start(struct elapsed* elapsed) { elapsed->start = clock(); }
static inline double elapsed_end(struct elapsed* elapsed)
{
    elapsed->end = clock();
    return elapsed_seconds(elapsed);
}

#endif
