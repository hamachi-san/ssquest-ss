// #include <memory.h>
// #include "sprite.h"

// static HashSet s_sprite_id_by_name;

// void registerSprite(const char* path, const char* filename)
// {
//   s_sprite_id_by_name.insert(filename, sprite_id);
// }

// Sprite* spriteCreate(const char* name)
// {
//   Sprite* sprite = malloc(sizeof(Sprite));
//   memset(sprite, 0, sizeof *sprite);

//   sprite->source.sprite_id = s_sprite_id_by_name.get(name);

//   return sprite;
// }

// void spriteDraw(const Sprite* sprite)
// {
//   jo_sprite_set_palette(sprite->source.palette_id);
//   jo_sprite_draw3D(sprite->source.sprite_id, sprite->x, sprite->y, 500);
// }
