#ifndef _TILE_H_
#define _TILE_H_

#include <stdbool.h>

typedef int pheremone_level_t;

typedef struct
{
  pheremone_level_t pheremone;
  bool has_ant;
  bool has_food;
} tile_t;

int tile_init(tile_t *tile);
char tile_render(tile_t tile);

#endif /* _TILE_H_ */