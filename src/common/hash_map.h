/**
 * ハッシュテーブル
 */
#ifndef COMMON_HASH_MAP_H_
#define COMMON_HASH_MAP_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct HashMap {
  /** テーブルの最大サイズ */
  uint32_t table_capacity;
  /** 実体は HashMapEntry のポインタ配列. voidポインタ * capacity の分だけ確保 */
  void** entry_table;
  /** 未使用エントリリストの先頭 */
  void* unused_entry_list_head;
  /** エントリ用バッファ. ここで確保されたメモリが unusedEntryListHead から繋がれ、entryTable に登録される */
  void* entry_buffer;
} HashMap;

extern HashMap* createHashMap(uint32_t initial_entry_capacity, uint32_t initial_table_capacity);
extern void destroyHashMap(HashMap** hash_map);
extern bool hashMapExists(const HashMap* hash_map, const char* key);
extern void hashMapInsert(HashMap* hash_map, const char* key, void* data);
extern uint32_t hashMapMakeIndex(const HashMap* hash_map, const char* key);

#endif
