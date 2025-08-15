#include "unity.h"
#include "common/hash_map.h"

extern void run_all_hash_map_tests();

int main(void)
{
  UNITY_BEGIN();

  run_all_hash_map_tests();

  return UNITY_END();
}
