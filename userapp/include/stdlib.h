#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/types.h>

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

typedef struct _div_t {
  int quot;
  int rem;
} div_t;

typedef struct _ldiv_t {
  long quot;
  long rem;
} ldiv_t;

div_t div (int numer, int denom);
ldiv_t ldiv (long int numer, long int denom);

void srand(unsigned int seed);
int rand();

void *malloc(size_t bytes);
void *calloc(size_t num, size_t size);
void *realloc(void *oldptr, size_t bytes);
void  free(void *ptr);

#endif /* _STDLIB_H */