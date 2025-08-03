/**
 * エントリーポイント
 *
 * Copyright (C) 2025, hamachi-san(ssgameuser@gmail.com)
 * All rights reserved.
 */
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <jo/jo.h>
#include "main.h"
#include "global_state.h"
#include "pad.h"

typedef void (*UpdateFunc)(void);

// 型定義
typedef int SpriteId;

// 関数の前置宣言
static void mainLoop(void);

static void onDraw(void);
static jo_palette* handlePaletteLoaded();
static void onUpdatePad(void);

// 毎フレーム呼び出される一連の関数
static const UpdateFunc s_update_functions[] = {
  // パッドの更新処理
  onUpdatePad,
  // 描画処理
  onDraw,
  // 番兵
  NULL,
};

static GlobalState g_global_state;
static Pad s_pad;
static jo_palette g_palette;
static jo_palette g_palette2;

static SpriteId g_sonic_id = -1;

/**
 * JoEngine から毎フレーム呼び出される唯一の処理
 */
static void mainLoop(void)
{
  globalStateOnUpdate(&g_global_state);
}

/**
 * ゲーム初期化処理
 */
void onInitialize(void)
{
  // パレットとスプライトの設定
  jo_set_tga_palette_handling(handlePaletteLoaded);
  g_sonic_id = jo_sprite_add_tga("TEX", "BALL.TGA", 1);
  jo_set_tga_palette_handling(JO_NULL);
  jo_create_palette(&g_palette2);
  memcpy(&g_palette2.data[0], &g_palette.data[0], sizeof g_palette.data[0] * 255);
  g_palette2.data[27] = JO_COLOR_RGB(255, 255, 255);

  jo_set_printf_color_index(JO_COLOR_INDEX_White);

  // パッドの設定
  padInitialize(&s_pad);
}

/**
 * ゲーム更新処理
 */
void onUpdate(void) {
  uint32_t index = 0;

  // 登録されている関数を全て呼び出す
  while (s_update_functions[index]) {
    s_update_functions[index]();
    ++index;
  }
}

/**
 * 描画処理
 */
static void onDraw(void)
{
  jo_sprite_set_palette(g_palette.id);
  jo_sprite_draw3D(g_sonic_id, 0, 0, 500);

  jo_sprite_set_palette(g_palette2.id);
  jo_sprite_draw3D(g_sonic_id, -100, -100, 500);
}

/**
 * パッド入力更新処理(& 画面表示)
 */
static void onUpdatePad(void)
{
  // 文字列表示クリア(ボタン定義数 + キー状態表示の分)
  for (size_t i = 0; i < PAD_BUTTONS_MAX + 1; ++i) {
    jo_clear_screen_line(i + 1);
  }

  static const uint32_t col = 0;

  // キー入力
  padUpdate(&s_pad);

  // キー状態を表示
  jo_printf(0, 0, "%04d", s_pad._state);

  // キー入力に応じて文字列表示
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_UP)) {
    jo_printf(col, 1, "PAD_UP");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_DOWN)) {
    jo_printf(col, 2, "PAD_DOWN");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_LEFT)) {
    jo_printf(col, 3, "PAD_LEFT");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_RIGHT)) {
    jo_printf(col, 4, "PAD_RIGHT");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_A)) {
    jo_printf(col, 5, "PAD_A");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_B)) {
    jo_printf(col, 6, "PAD_B");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_C)) {
    jo_printf(col, 7, "PAD_C");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_X)) {
    jo_printf(col, 8, "PAD_X");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_Y)) {
    jo_printf(col, 9, "PAD_Y");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_Z)) {
    jo_printf(col, 10, "PAD_Z");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_L)) {
    jo_printf(col, 11, "PAD_L");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_R)) {
    jo_printf(col, 12, "PAD_R");
  }
  if (padIsButtonPressed(&s_pad, PAD_BUTTON_BITS_START)) {
    jo_printf(col, 13, "PAD_START");
  }
}

/**
 * TGA 読み込み時のパレット作成処理
 */
static jo_palette* handlePaletteLoaded()
{
  jo_create_palette(&g_palette);
  return &g_palette;
}

/**
 * エントリーポイント
 */
void jo_main(void)
{
  // エンジンの初期化
  jo_core_init(JO_COLOR_Purple);

  // ステート初期化
  globalStateInitialize(&g_global_state);

  // 唯一のステート処理関数をコールバック登録
  jo_core_add_callback(mainLoop);

  // 実行開始
  jo_core_run();
}
