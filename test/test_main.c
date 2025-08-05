#include "unity.h"
#include "common/hash_map.h"

void setUp(void)
{
  // 各テストの前に毎回実行される処理
}

void tearDown(void)
{
  // 各テストの後に毎回実行される処理
}

void test_main(void)
{
  // テストを記述
}


int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_main);
  return UNITY_END();
}
