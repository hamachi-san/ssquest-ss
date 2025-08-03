#include "ball.h"
#include <jo/jo.h>
#include <stdint.h>
#include "wrapper/math.h"

static const uint32_t BALL_WIDTH = 48;
static const uint32_t BALL_HEIGHT = 48;
static const uint32_t BALL_WIDTH_2 = BALL_WIDTH >> 1;
static const uint32_t BALL_HEIGHT_2 = BALL_HEIGHT >> 1;
static const int32_t SCREEN_LEFT = -JO_TV_WIDTH_2;
static const int32_t SCREEN_TOP = -JO_TV_HEIGHT_2;
static const int32_t SCREEN_RIGHT = JO_TV_WIDTH_2;
static const int32_t SCREEN_BOTTOM = JO_TV_HEIGHT_2;

inline int32_t fromFixed(int32_t value)
{
  return value >> 16;
}

inline int32_t toFixed(int32_t value)
{
  return value << 16;
}

void ballInitialize(Ball* ball, SpriteId sprite_id, PaletteId palette_id)
{
  ball->x = ball->y = 0;
  ball->vx = ball->vy = 0;
  ball->sprite_id = 0;

  ball->vx = (getRandom() % (4 << 16)) - (getRandom() % (2 << 16));
  ball->vy = (getRandom() % (4 << 16)) - (getRandom() % (2 << 16));

  ball->sprite_id = sprite_id;
  ball->palette_id = palette_id;
}

void ballOnUpdate(Ball* ball)
{
  ball->x += ball->vx;
  ball->y += ball->vy;

  if (fromFixed(ball->x) < SCREEN_LEFT + (int32_t)BALL_WIDTH_2) {
    ball->x = toFixed(SCREEN_LEFT + (int32_t)BALL_WIDTH_2);
    ball->vx *= -1;
  }

  if (SCREEN_RIGHT < fromFixed(ball->x) + (int32_t)BALL_WIDTH_2) {
    ball->x = toFixed(SCREEN_RIGHT - (int32_t)BALL_WIDTH_2);
    ball->vx *= -1;
  }

  if (fromFixed(ball->y) < SCREEN_TOP) {
    ball->y = toFixed(SCREEN_TOP + (int32_t)BALL_HEIGHT_2);
    ball->vy *= -1;
  }

  if (SCREEN_BOTTOM < fromFixed(ball->y) + (int32_t)BALL_HEIGHT_2) {
    ball->y = toFixed(SCREEN_BOTTOM - (int32_t)BALL_HEIGHT_2);
    ball->vy *= -1;
  }
}

void ballOnDraw(const Ball* ball)
{
  jo_sprite_set_palette(ball->palette_id);
  jo_sprite_draw3D(ball->sprite_id, fromFixed(ball->x), fromFixed(ball->y), 500);
}
