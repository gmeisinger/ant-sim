#ifndef _ANT_H_
#define _ANT_H_

#include <stdint.h>

#include "food.h"
#include "tile.h"
#include <stdbool.h>

typedef struct
{
  int x;
  int y;
} position_t;

typedef struct
{
  position_t pos;
  tile_t *surroundings[9];
} entity_state_t;

typedef struct
{
  uint8_t dir;
  bool has_food;
} ant_t;

void ant_init(ant_t **ant, entity_state_t *state, int x, int y);
void ant_update(ant_t *ant, entity_state_t *state);
void ant_destroy(ant_t **ant);

#endif /* _ANT_H_ */