/**
 * キー入力をプラットフォーム固有のAPIから切り離すためのラッパー
 */
#ifndef WRAPPER_INPUT_H_
#define WRAPPER_INPUT_H_

#include <assert.h>
#include <stdint.h>

/**
 * ボタン定義
 */
enum Key {
  KEY_UP = 0,
  KEY_DOWN,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_A,
  KEY_B,
  KEY_C,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_L,
  KEY_R,
  KEY_START,
  KEY_MAX,
};

/**
 * ボタンのビットパターン
 */
enum KeyBit {
  KEY_BIT_UP = 0x01 << KEY_UP,
  KEY_BIT_DOWN = 0x01 << KEY_DOWN,
  KEY_BIT_LEFT = 0x01 << KEY_LEFT,
  KEY_BIT_RIGHT = 0x01 << KEY_RIGHT,
  KEY_BIT_A = 0x01 << KEY_A,
  KEY_BIT_B = 0x01 << KEY_B,
  KEY_BIT_C = 0x01 << KEY_C,
  KEY_BIT_X = 0x01 << KEY_X,
  KEY_BIT_Y = 0x01 << KEY_Y,
  KEY_BIT_Z = 0x01 << KEY_Z,
  KEY_BIT_L = 0x01 << KEY_L,
  KEY_BIT_R = 0x01 << KEY_R,
  KEY_BIT_START = 0x01 << KEY_START,
};

/**
 * キー定義からキーステートのビット状態に変換
 *
 * @param key キー定義
 * @return キーステートのビット状態
 */
inline uint32_t keyToKeyBit(uint32_t key)
{
  assert(key < KEY_MAX);
  return 0x01 << key;
}

extern uint32_t getKeyState(void);

#endif // WRAPPER_INPUT_H_
