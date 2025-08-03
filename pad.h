/**
 * パッドからの入力インターフェース
 */
#ifndef PAD_H_
#define PAD_H_

#include <stdint.h>

/**
 * ボタン定義
 */
enum PadButtons {
  PAD_BUTTONS_UP = 0,
  PAD_BUTTONS_DOWN,
  PAD_BUTTONS_LEFT,
  PAD_BUTTONS_RIGHT,
  PAD_BUTTONS_A,
  PAD_BUTTONS_B,
  PAD_BUTTONS_C,
  PAD_BUTTONS_X,
  PAD_BUTTONS_Y,
  PAD_BUTTONS_Z,
  PAD_BUTTONS_L,
  PAD_BUTTONS_R,
  PAD_BUTTONS_START,
  PAD_BUTTONS_MAX,
};

/**
 * ボタンのビットパターン
 */
enum PadButtonBits {
  PAD_BUTTON_BITS_UP    = 0x01 << PAD_BUTTONS_UP,
  PAD_BUTTON_BITS_DOWN  = 0x01 << PAD_BUTTONS_DOWN,
  PAD_BUTTON_BITS_LEFT  = 0x01 << PAD_BUTTONS_LEFT,
  PAD_BUTTON_BITS_RIGHT = 0x01 << PAD_BUTTONS_RIGHT,
  PAD_BUTTON_BITS_A     = 0x01 << PAD_BUTTONS_A,
  PAD_BUTTON_BITS_B     = 0x01 << PAD_BUTTONS_B,
  PAD_BUTTON_BITS_C     = 0x01 << PAD_BUTTONS_C,
  PAD_BUTTON_BITS_X     = 0x01 << PAD_BUTTONS_X,
  PAD_BUTTON_BITS_Y     = 0x01 << PAD_BUTTONS_Y,
  PAD_BUTTON_BITS_Z     = 0x01 << PAD_BUTTONS_Z,
  PAD_BUTTON_BITS_L     = 0x01 << PAD_BUTTONS_L,
  PAD_BUTTON_BITS_R     = 0x01 << PAD_BUTTONS_R,
  PAD_BUTTON_BITS_START = 0x01 << PAD_BUTTONS_START,
};

typedef struct tagPad {
  /** キー状態 */
  uint32_t _state;
  /** 前のフレームのキー状態 */
  uint32_t _prev_state;
} Pad;

// 初期化処理
extern void padInitialize(Pad *pad);
// 更新処理
extern void padUpdate(Pad *pad);
// 指定のボタンが押下状態であるかを取得する
extern bool padIsButtonPressed(const Pad* pad, uint32_t button_bit);
// 指定のボタンが押下されたかを取得する
extern bool padIsButtonPushed(const Pad* pad, uint32_t button_bit);

#endif // PAD_H_
