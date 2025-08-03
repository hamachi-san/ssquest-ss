#include "math.h"
#include <jo/jo.h>
#include <stdint.h>

uint32_t getRandom(void)
{
  return jo_random(INT32_MAX);
}
