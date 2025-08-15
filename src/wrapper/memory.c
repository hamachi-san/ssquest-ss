#include "memory.h"
#include <assert.h>

#ifdef UNIT_TEST
#include <stdlib.h>
#include <stdio.h>
#else
#include <jo/jo.h>
#endif // UNIT_TEST

#ifdef UNIT_TEST
uintptr_t* myMalloc(size_t size)
{
  assert(0 < size);
  return malloc(size);
}

void myFree(void* p)
{
  if (p) {
    free(p);
  }
}

#else

uintptr_t* myMalloc(size_t size)
{
  assert(0 < size);
  return jo_malloc(size);
}

void myFree(void* p)
{
  if (p) {
    jo_free(p);
  }
}

#endif // UNIT_TEST
