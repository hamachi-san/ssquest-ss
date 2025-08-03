/**
 * パッドからの入力インターフェース
 */
#ifndef PAD_H_
#define PAD_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct tagPad {
  /** キー状態 */
  uint32_t _state;
  /** 前のフレームのキー状態 */
  uint32_t _prev_state;
} Pad;

// 初期化処理
extern void padInitialize(Pad* pad);
// 更新処理
extern void padUpdate(Pad* pad);
// 指定のボタンが押下状態であるかを取得する
extern bool padIsButtonPressed(const Pad* pad, uint32_t button_bit);
// 指定のボタンが押下されたかを取得する
extern bool padIsButtonPushed(const Pad* pad, uint32_t button_bit);

#endif // PAD_H_
