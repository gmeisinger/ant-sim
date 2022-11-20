#ifndef _ANT_H_
#define _ANT_H_

#include "entity.h"
#include <stdint.h>

typedef struct
{
  uint8_t dir;
  bool has_food;
} ant_t;

void ant_init(ant_t **ant, entity_state_t *state);

#endif /* _ANT_H_ */