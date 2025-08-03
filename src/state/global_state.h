/**
 * グローバルのゲームステート定義/管理
 */
#ifndef GLOBAL_STATE_H_
#define GLOBAL_STATE_H_

#include <stdint.h>

typedef struct tagGlobalState {
  uint32_t _state;
} GlobalState;

// 初期化処理
void globalStateInitialize(GlobalState* state);
// 毎フレームの更新処理
void globalStateOnUpdate(GlobalState* state);

#endif // GLOBAL_STATE_H_
