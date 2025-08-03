#include <assert.h>
#include <jo/jo.h>
#include "pad.h"

/**
 * 初期化処理
 *
 * @param pad 対象の Pad 構造体へのポインタ
 */
void padInitialize(Pad *pad) {
  pad->_state = 0;
  pad->_prev_state = 0;
}

/**
 * 更新処理
 * ゲームパッドからキー入力を取得する
 * キーの状態を Pad::_prev_state を更新し、Pad::_state を更新する
 */
void padUpdate(Pad *pad) {
  assert(pad);

  // 前フレームでのキー入力状態を保存(新たに押下されたボタンを検出するため)
  pad->_prev_state = pad->_state;

  const int32_t port = 0;
  uint32_t button_state = 0;

  // 各キーの押下状態を取得し、押されている部分だけ立っているビットフィールドを作成する
  button_state |= jo_is_input_key_pressed(port, JO_KEY_UP)    ? PAD_BUTTON_BITS_UP    : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_DOWN)  ? PAD_BUTTON_BITS_DOWN  : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_LEFT)  ? PAD_BUTTON_BITS_LEFT  : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_RIGHT) ? PAD_BUTTON_BITS_RIGHT : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_A)     ? PAD_BUTTON_BITS_A     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_B)     ? PAD_BUTTON_BITS_B     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_C)     ? PAD_BUTTON_BITS_C     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_X)     ? PAD_BUTTON_BITS_X     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_Y)     ? PAD_BUTTON_BITS_Y     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_Z)     ? PAD_BUTTON_BITS_Z     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_L)     ? PAD_BUTTON_BITS_L     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_R)     ? PAD_BUTTON_BITS_R     : 0;
  button_state |= jo_is_input_key_pressed(port, JO_KEY_START) ? PAD_BUTTON_BITS_START : 0;

  pad->_state = button_state;
}

/**
 * 指定のボタンが押下状態であるかを取得する
 *
 * @param pad        Pad 構造体へのポインタ
 * @param button_bit 取得したいボタンのビットパターン
 *
 * @return 押下状態なら true
 */
bool padIsButtonPressed(const Pad* pad, uint32_t button_bit)
{
  assert(pad);

  return !!(pad->_state & button_bit);
}

/**
 * 指定のボタンが押下状態であるかを取得する
 *
 * @param pad        Pad 構造体へのポインタ
 * @param button_bit 取得したいボタンのビットパターン
 *
 * @return 押下状態なら true
 */
bool padIsButtonPushed(const Pad* pad, uint32_t button_bit)
{
  assert(pad);

  return !!((pad->_state & ~pad->_prev_state) & button_bit);
}
