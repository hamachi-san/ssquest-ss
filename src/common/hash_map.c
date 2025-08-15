/**
 * ハッシュテーブル実装
 */
#include <memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "hash_map.h"
#include "wrapper/memory.h"

#define KEY_SIZE  (128)

// 関数の前方宣言
static uint32_t makeFnv1aHash(const char* key);

/**
 * ハッシュテーブルに格納されるエントリ
 */
typedef struct HashMapNode {
  /** キー名 */
  char key[KEY_SIZE];
  /** データへのポインタ */
  void* data;
  /** 未使用時/キーが重複している際の次のエントリへのポインタ */
  struct HashMapNode* next;
} HashMapNode;

/**
 * ハッシュテーブルを作成する
 * 破棄時は必ず destroyHashMap() を用いて破棄すること
 *
 * @param initial_entry_capacity 最初に確保する最大容量
 * @param initial_table_capacity ハッシュテーブルのサイズ
 * @return 生成したハッシュテーブルへのポインタ
 */
HashMap* createHashMap(uint32_t initial_entry_capacity, uint32_t initial_table_capacity)
{
  // ハッシュテーブルに格納するエントリの作成
  // initial_entry_capacity 分のインスタンスを確保し、リストを繋げる
  const uint32_t buffer_allocation_size = initial_entry_capacity * sizeof(uintptr_t);
  HashMapNode* buffer = (HashMapNode*)myMalloc(buffer_allocation_size);
  memset(buffer, 0, buffer_allocation_size);
  HashMapNode* entries = &buffer[0];

  for (uint32_t i = 0; i < initial_entry_capacity; ++i) {
    HashMapNode* current = &entries[i];
    current->next = NULL;

    if (0 < i) {
      HashMapNode* prev = &entries[i - 1];
      prev->next = current;
    }
  }

  // ハッシュテーブルそのものの作成
  const uint32_t hash_table_allocation_size = initial_table_capacity * sizeof(uintptr_t);
  HashMapNode** hash_table = (HashMapNode**)myMalloc(hash_table_allocation_size);
  memset(hash_table, 0, hash_table_allocation_size);

  HashMap* hash_map = (HashMap*)myMalloc(sizeof(HashMap));
  hash_map->entry_buffer = buffer;
  hash_map->entry_table = (void**)hash_table;
  hash_map->unused_entry_list_head = &entries[0];
  hash_map->table_capacity = initial_table_capacity;

  return hash_map;
}

/**
 * ハッシュテーブルの破棄を行う
 * 渡したポインタも NULL でクリアされる
 *
 * @param hash_map 破棄対象のハッシュテーブルのポインタへのポインタ
 */
void destroyHashMap(HashMap** hash_map)
{
  myFree((*hash_map)->entry_table);
  (*hash_map)->entry_table = NULL;

  myFree((*hash_map)->entry_buffer);
  (*hash_map)->entry_buffer = NULL;

  myFree(*hash_map);
  *hash_map = NULL;
}

bool hashMapExists(const HashMap* hash_map, const char* key)
{
  const uint32_t index = hashMapMakeIndex(hash_map, key);
  HashMapNode* node = (HashMapNode*)hash_map->entry_table[index];

  if (!node) {
    return false;
  }

  if (strcmp(key, node->key) == 0) {
    return true;
  }

  // キーが異なる = 重複が存在するためリストを辿って検索
  node = node->next;

  while (node) {
    if (strcmp(key, node->key) == 0) {
      return true;
    }

    node = node->next;
  }

  // 最後まで辿ったがキーがない
  return false;
}

void hashMapInsert(HashMap* hash_map, const char* key, void* data)
{
  if (!hash_map->unused_entry_list_head) {
    // 枯渇している
    // TODO: 自動拡張
    return;
  }

  HashMapNode* insert_node = hash_map->unused_entry_list_head;
  hash_map->unused_entry_list_head = insert_node->next;
  insert_node->next = NULL;
  strcpy(insert_node->key, key);
  insert_node->data = data;

  const uint32_t index = hashMapMakeIndex(hash_map, key);
  HashMapNode* node = (HashMapNode*)hash_map->entry_table[index];

  // 該当のインデックスが空きの場合はそこへ格納して終了
  if (!node) {
    hash_map->entry_table[index] = insert_node;
    return;
  }

  // 既にそのインデックスが使用されている場合(重複インデックスが発生した場合)は
  // リストの末尾まで辿る
  while (node->next) {
    node = node->next;
  }

  node->next = insert_node;
}

/**
 * キーからテーブルのインデックスを作成する
 *
 * @param key テーブルのキー
 */
uint32_t hashMapMakeIndex(const HashMap* hash_map, const char* key)
{
  return makeFnv1aHash(key) % hash_map->table_capacity;
}

/**
 * キーからテーブルのインデックスを作成する
 *
 * @param key テーブルのキー
 */
static uint32_t makeFnv1aHash(const char* key)
{
  uint32_t hash = 2166136261;

  for (size_t i = 0; i < KEY_SIZE && *key != '0'; ++key) {
    hash ^= (uint8_t)*key;
    hash *= 16777619;
  }

  return hash;
}
