/**
 * エントリーポイント
 *
 * Copyright (C) 2025, hamachi-san(ssgameuser@gmail.com)
 * All rights reserved.
 */
#include "main.h"
#include <jo/jo.h>
#include <memory.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "game/ball.h"
#include "game/pad/pad.h"
#include "game/state/global_state.h"
#include "wrapper/input.h"
#include "wrapper/math.h"

typedef void (*UpdateFunc)(void);

// 関数の前置宣言
static void mainLoop(void);

static jo_palette* handlePaletteLoaded();

static void onUpdatePad(void);
static void onUpdateBall(void);
static void animatePalette(void);
static void onDrawBall(void);

// 毎フレーム呼び出される一連の関数
static const UpdateFunc s_update_functions[] = {
  // パッドの更新処理
  onUpdatePad,
  // ボールの更新処理
  onUpdateBall,
  // マスターパレットのパレットアニメーション
  animatePalette,
  // 描画処理
  onDrawBall,
  // 番兵
  NULL,
};

// ゲームステートとパッド入力データ
static GlobalState g_global_state;
static Pad s_pad;

// パレットのデータ
enum { PALETTE_COUNT = 6 };
static jo_palette s_palettes[PALETTE_COUNT];
static const uint32_t BALL_COLOR_INDEX = 27;
// 0番パレットの R, G, B
static uint32_t s_master_colors[3];
// 0番パレットの アニメーション量
static int32_t s_master_color_vectors[3];

// ボールのデータ
enum { BALL_COUNT = 256 };
static Ball s_balls[BALL_COUNT];
static uint32_t s_enable_ball_count = 0;

/**
 * TGA 読み込み時のパレット作成処理
 * パレット0番を渡して、そこに設定してもらう
 */
static jo_palette* handlePaletteLoaded()
{
  jo_create_palette(&s_palettes[0]);
  return &s_palettes[0];
}

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
  // print 文の文字を白に設定
  jo_set_printf_color_index(JO_COLOR_INDEX_White);

  // TGA からボールの画像を読み込み、パレットをロードする
  jo_set_tga_palette_handling(handlePaletteLoaded);
  const SpriteId sprite_id = jo_sprite_add_tga("TEX", "BALL.TGA", 1);
  jo_set_tga_palette_handling(JO_NULL);

  // ロードしたパレットの、ボールの色にあたる部分を適当に変える
  jo_palette* original_palette = &s_palettes[0];
  s_master_colors[0] = getRandom() % 255;
  s_master_colors[1] = getRandom() % 255;
  s_master_colors[2] = getRandom() % 255;
  original_palette->data[BALL_COLOR_INDEX] = JO_COLOR_RGB(s_master_colors[0], s_master_colors[1], s_master_colors[2]);

  // 色の変化方向も適当に決める
  for (int i = 0; i < 3; ++i) {
    s_master_color_vectors[i] = getRandom() % 16 - getRandom() % 8;
  }

  // 0 番のパレットを複製して PALETTE_COUNT 個分パレットを作成する
  for (size_t i = 1; i < PALETTE_COUNT; ++i) {
    jo_palette* palette = &s_palettes[i];

    jo_create_palette(palette);
    memcpy(&palette->data[0], &original_palette->data[0], sizeof palette->data[0] * 255);
    palette->data[BALL_COLOR_INDEX] =
      JO_COLOR_RGB(getRandom() % 255, getRandom() % 255, getRandom() % 255); // ランダムに色を決める
  }

  // パッドの設定
  padInitialize(&s_pad);

  // ボール作成
  for (size_t i = 0; i < BALL_COUNT; ++i) {
    // ボール0番のみ0番パレット固定、その他は1〜を順に設定
    uint32_t palette_index = i == 0 ? 0 : 1 + i % (PALETTE_COUNT - 1);

    ballInitialize(&s_balls[i], sprite_id, s_palettes[palette_index].id);
  }
}

/**
 * ゲーム更新処理
 */
void onUpdate(void)
{
  uint32_t index = 0;

  // 登録されている関数を全て呼び出す
  while (s_update_functions[index]) {
    s_update_functions[index]();
    ++index;
  }
}

/**
 * パッド入力更新処理(& 画面表示)
 */
static void onUpdatePad(void)
{
  // 文字列表示クリア(ボタン定義数 + キー状態表示の分)
  for (size_t i = 0; i < KEY_MAX + 1; ++i) {
    jo_clear_screen_line(i + 1);
  }

  static const uint32_t col = 0;

  // キー入力
  padUpdate(&s_pad);

  // // キー状態を表示
  // jo_printf(0, 0, "%04d", s_pad._state);

  // キー入力に応じて文字列表示
  if (padIsButtonPressed(&s_pad, KEY_UP)) {
    jo_printf(col, 1, "PAD_UP");

    if (s_enable_ball_count < BALL_COUNT) {
      ++s_enable_ball_count;
    }
  }
  if (padIsButtonPressed(&s_pad, KEY_DOWN)) {
    jo_printf(col, 2, "PAD_DOWN");

    if (0 < s_enable_ball_count) {
      --s_enable_ball_count;
    }
  }
  if (padIsButtonPressed(&s_pad, KEY_LEFT)) {
    jo_printf(col, 3, "PAD_LEFT");
  }
  if (padIsButtonPressed(&s_pad, KEY_RIGHT)) {
    jo_printf(col, 4, "PAD_RIGHT");
  }
  if (padIsButtonPressed(&s_pad, KEY_A)) {
    jo_printf(col, 5, "PAD_A");
  }
  if (padIsButtonPressed(&s_pad, KEY_B)) {
    jo_printf(col, 6, "PAD_B");
  }
  if (padIsButtonPressed(&s_pad, KEY_C)) {
    jo_printf(col, 7, "PAD_C");
  }
  if (padIsButtonPressed(&s_pad, KEY_X)) {
    jo_printf(col, 8, "PAD_X");
  }
  if (padIsButtonPressed(&s_pad, KEY_Y)) {
    jo_printf(col, 9, "PAD_Y");
  }
  if (padIsButtonPressed(&s_pad, KEY_Z)) {
    jo_printf(col, 10, "PAD_Z");
  }
  if (padIsButtonPressed(&s_pad, KEY_L)) {
    jo_printf(col, 11, "PAD_L");
  }
  if (padIsButtonPressed(&s_pad, KEY_R)) {
    jo_printf(col, 12, "PAD_R");
  }
  if (padIsButtonPressed(&s_pad, KEY_START)) {
    jo_printf(col, 13, "PAD_START");
  }

  // A or B or C ボタンが押されていたらボール 0 個にする
  if (padIsButtonPressedKeyBit(&s_pad, KEY_BIT_A | KEY_BIT_B | KEY_BIT_C)) {
    s_enable_ball_count = 0;
  }
}

/**
 * ボールの移動処理(を呼び出す)
 */
static void onUpdateBall(void)
{
  for (size_t i = 0; i < s_enable_ball_count; ++i) {
    ballOnUpdate(&s_balls[i]);
  }
}

/**
 * 0番パレットをアニメーションする
 */
static void animatePalette(void)
{
  for (int i = 0; i < 3; ++i) {
    int32_t color = (int32_t)s_master_colors[i] + s_master_color_vectors[i];

    // 0-255 の範囲を出たら逆方向へ
    if (color < 0) {
      color = 0;
      s_master_color_vectors[i] *= -1;
    }

    if (255 < color) {
      color = 255;
      s_master_color_vectors[i] *= -1;
    }

    s_master_colors[i] = (uint32_t)color;
  }

  s_palettes[0].data[BALL_COLOR_INDEX] = JO_COLOR_RGB(s_master_colors[0], s_master_colors[1], s_master_colors[2]);
}

/**
 * ボールの描画処理
 */
static void onDrawBall(void)
{
  // ボールの数を表示
  jo_clear_screen_line(0);
  jo_printf(0, 0, "%03d", s_enable_ball_count);

  for (size_t i = 0; i < s_enable_ball_count; ++i) {
    ballOnDraw(&s_balls[i]);
  }
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
