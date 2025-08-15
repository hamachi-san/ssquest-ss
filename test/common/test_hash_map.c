#include <stdbool.h>
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

/**
 * hashMapMakeIndex() のテスト
 */
void test_hashMapMakeIndex(void)
{
  const uint32_t entry_size = 256;
  const char* keys[] = {
    "char",
    "short",
    "int",
    "long",
    "unsigned char",
    "unsigned short",
    "unsigned int",
    "unsigned long",
    "const",
    "void",
    "NULL",
    "return",
    "for",
    "while",
    "switch",
    "case",
    "break",
    "continue",
    "typedef",
    "define",
    "if",
    "else",
    "endif",
  };

  const uint32_t keys_size = sizeof keys / sizeof keys[0];
  HashMap* hash_map = createHashMap(entry_size, entry_size);
  bool results[256] = { false };
  bool duplicate = false;

  for (size_t i = 0; i < keys_size; ++i) {
    uint32_t index = hashMapMakeIndex(hash_map, keys[i]);

    if (results[index]) {
      duplicate = true;
      break;
    }

    results[index] = true;
  }

  // 重複なし
  TEST_ASSERT_FALSE(duplicate);

  destroyHashMap(&hash_map);
}

/**
 * hashMapExists() のテスト
 */
void test_hashMapExists(void)
{
  const uint32_t table_size = 256;
  HashMap* hash_map = createHashMap(table_size, table_size);
  int data = 123;

  // まだ何も入れてない
  TEST_ASSERT_FALSE(hashMapExists(hash_map, "test"));

  // データ投入
  hashMapInsert(hash_map, "test", &data);
  TEST_ASSERT_TRUE(hashMapExists(hash_map, "test"));

  // 投入したものとは別のキーを調べる
  TEST_ASSERT_FALSE(hashMapExists(hash_map, "test2"));

  destroyHashMap(&hash_map);
}

/**
 * 重複インデックス発生時のテスト
 */
void test_at_duplicate_index(void)
{
  // テーブルサイズを2にすれば、3件データ投入した際に1件は重複するはず
  const uint32_t entry_size = 3;
  const uint32_t table_size = 2;

  HashMap* hash_map = createHashMap(entry_size, table_size);
  int data[] = { 123, 456, 789 };

  // データ1投入
  hashMapInsert(hash_map, "test", &data[0]);
  TEST_ASSERT_TRUE(hashMapExists(hash_map, "test"));

  // データ2投入
  hashMapInsert(hash_map, "test2", &data[1]);
  TEST_ASSERT_TRUE(hashMapExists(hash_map, "test2"));

  // データ3投入
  hashMapInsert(hash_map, "test3", &data[2]);
  TEST_ASSERT_TRUE(hashMapExists(hash_map, "test3"));

  destroyHashMap(&hash_map);
}

/**
 * HashMap 初期化/破棄のテスト
 */
void test_createHashMap(void)
{
  // テーブルサイズと要素数が同じ
  {
    HashMap* hash_map;
    hash_map = createHashMap(128, 128);
    destroyHashMap(&hash_map);
    TEST_ASSERT_NULL(hash_map);
  }

  // テーブルサイズ < 要素数
  {
    HashMap* hash_map;
    hash_map = createHashMap(256, 128);
    destroyHashMap(&hash_map);
    TEST_ASSERT_NULL(hash_map);
  }

  // テーブルサイズ > 要素数
  {
    HashMap* hash_map;
    hash_map = createHashMap(128, 256);
    destroyHashMap(&hash_map);
    TEST_ASSERT_NULL(hash_map);
  }
}

void run_all_hash_map_tests()
{
  RUN_TEST(test_hashMapMakeIndex);
  RUN_TEST(test_createHashMap);
  RUN_TEST(test_hashMapExists);
  RUN_TEST(test_at_duplicate_index);
}
