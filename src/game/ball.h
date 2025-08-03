#ifndef GAME_BALL_H_
#define GAME_BALL_H_

#include <stdint.h>

typedef int32_t SpriteId;
typedef int32_t PaletteId;

typedef struct tagBall {
  // 表示X座標(小数部16bitの固定小数)
  int32_t x;
  // 表示Y座標(小数部16bitの固定小数)
  int32_t y;
  // X方向移動量(小数部16bitの固定小数)
  int32_t vx;
  // Y方向移動量(小数部16bitの固定小数)
  int32_t vy;
  // 使用スプライトID
  SpriteId sprite_id;
  // 使用パレットID
  PaletteId palette_id;
} Ball;

void ballInitialize(Ball* ball, SpriteId sprite_id, PaletteId palette_id);
void ballOnUpdate(Ball* ball);
void ballOnDraw(const Ball* ball);

#endif // GAME_BALL_H_
