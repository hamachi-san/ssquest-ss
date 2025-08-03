#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <jo/jo.h>
#include "global_state.h"
#include "main.h"

// 前置宣言
typedef void (*StateFunc)(GlobalState*);
static void onStateInitialize(GlobalState* state);
static void onStateMain(GlobalState* state);

// ステート
enum _GlobalState {
  GLOBAL_STATE_NULL,
  GLOBAL_STATE_INITIALIZE,
  GLOBAL_STATE_MAIN,
};

// 各ステートで呼び出す関数の定義
static const StateFunc s_state_functions[] = {
  NULL,              // GLOBAL_STATE_NULL
  onStateInitialize, // GLOBAL_STATE_INITIALIZE
  onStateMain,       // GLOBAL_STATE_MAIN
};

/**
 * 毎フレームの更新処理を実行する
 *
 * @param globalState グローバルステート構造体へのポインタ
 */
void globalStateInitialize(GlobalState *state)
{
  assert(state);

  state->_state = GLOBAL_STATE_INITIALIZE;
}

/**
 * 毎フレームの更新処理を実行する
 *
 * @param globalState グローバルステート構造体へのポインタ
 */
void globalStateOnUpdate(GlobalState *state)
{
  assert(state);

  // ステートに対応した関数を呼び出す
  // ステートが更新されていたら新ステートの処理を再度呼び出す
  uint32_t prev_state = GLOBAL_STATE_NULL;

  while (state->_state != prev_state) {
    prev_state = state->_state;
    s_state_functions[state->_state](state);
  }
}

/**
 * GLOBAL_STATE_INITIALIZE 時の処理
 */
static void onStateInitialize(GlobalState* state)
{
  assert(state);

  // main.c で定義されている関数を呼び出す
  onInitialize();

  // ステートを更新して次へ遷移
  ++state->_state;
}

/**
 * GLOBAL_STATE_MAIN 時の処理
 */
static void onStateMain(GlobalState* state)
{
  assert(state);

  // main.c で定義されている関数を呼び出す
  onUpdate();
}
