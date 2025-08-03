#include "input.h"
#include <jo/jo.h>

uint32_t getKeyState(void)
{
  const uint32_t port = 0;
  uint32_t key_state = 0;

  // 各キーの押下状態を取得し、押されている部分だけ立っているビットフィールドを作成する
  key_state |= jo_is_input_key_pressed(port, JO_KEY_UP) ? KEY_BIT_UP : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_DOWN) ? KEY_BIT_DOWN : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_LEFT) ? KEY_BIT_LEFT : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_RIGHT) ? KEY_BIT_RIGHT : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_A) ? KEY_BIT_A : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_B) ? KEY_BIT_B : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_C) ? KEY_BIT_C : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_X) ? KEY_BIT_X : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_Y) ? KEY_BIT_Y : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_Z) ? KEY_BIT_Z : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_L) ? KEY_BIT_L : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_R) ? KEY_BIT_R : 0;
  key_state |= jo_is_input_key_pressed(port, JO_KEY_START) ? KEY_BIT_START : 0;

  return key_state;
}
