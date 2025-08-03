#include "pad.h"
#include <assert.h>
#include <jo/jo.h>
#include "wrapper/input.h"

/**
 * 初期化処理
 *
 * @param pad 対象の Pad 構造体へのポインタ
 */
void padInitialize(Pad* pad)
{
  pad->_state = 0;
  pad->_prev_state = 0;
}

/**
 * 更新処理
 * ゲームパッドからキー入力を取得する
 * 前フレームのキーの状態を Pad::_prev_state に更新し、Pad::_state を現在の状態に更新する
 */
void padUpdate(Pad* pad)
{
  assert(pad);

  // 前フレームでのキー入力状態を保存(新たに押下されたボタンを検出するため)
  pad->_prev_state = pad->_state;

  pad->_state = getKeyState();
}

/**
 * 指定のボタンが押下状態であるかを取得する
 *
 * @param pad Pad 構造体へのポインタ
 * @param key 取得したいボタンのキー定義
 *
 * @return 押下状態なら true
 */
bool padIsButtonPressed(const Pad* pad, uint32_t key)
{
  assert(pad);

  return !!(pad->_state & keyToKeyBit(key));
}

/**
 * 指定のボタンがこのフレーム押下されたかを取得する
 *
 * @param pad Pad 構造体へのポインタ
 * @param key 取得したいボタンのキー定義
 *
 * @return 押下されたなら true
 */
bool padIsButtonPushed(const Pad* pad, uint32_t key)
{
  assert(pad);

  return !!((pad->_state & ~pad->_prev_state) & keyToKeyBit(key));
}
