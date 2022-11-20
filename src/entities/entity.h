// typedef enum
// {
//   N,
//   NE,
//   E,
//   SE,
//   S,
//   SW,
//   W,
//   NW
// } direction_t;

#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "food.h"
#include "tile.h"
#include <stdbool.h>

typedef int pheremone_level_t;

typedef struct
{
  int x;
  int y;
} position_t;

typedef struct
{
  position_t pos;
  uint8_t dir;
  tile_t *surroundings[9];
} entity_state_t;

typedef struct
{
  void (*init)(entity_state_t *initial_state);
  void (*update)(entity_state_t *new_state);
  void (*destroy)(void);
} entity_t;

typedef stuct
{
  entity_t *p;
}
ant_t;

// switch (dir)
// {
// case N:
// {
// }
// break;
// case NE:
// {
// }
// break;
// case E:
// {
// }
// break;
// case SE:
// {
// }
// break;
// case S:
// {
// }
// break;
// case SW:
// {
// }
// break;
// case W:
// {
// }
// break;
// case NW:
// {
// }
// break;
// }

#endif /* _ENTITY_H_*/