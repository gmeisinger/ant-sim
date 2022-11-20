#include "entity.h"
#include "direction.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static entity_t *self;
static uint8_t dir;

void init(entity_state_t *state)
{
  self = malloc(sizeof(entity_t));
  dir  = init_direction();
}

void update(entity_state_t *current_state)
{
  static uint8_t available_tiles;
  tile_t *next_selected_tile;

  int max_pheremone = 0;
  for (unsigned i = 0; i < sizeof(current_state->surroundings) / sizeof(tile_t); i++)
    {
      tile_t *tile = current_state->surroundings[i];

      if (tile->pheremone == -1)
      {
        available_tiles &= ~(1 << i);
        continue;
      }
      available_tiles |= (1 << i);
      /**
       * CALCULATE DIRECTION
       */
      // if (dir & NORTHEAST)
      //   {
      //   }
      // else if (dir & NORTHWEST)
      //   {
      //   }
      // else if (dir & SOUTHEAST)
      //   {
      //   }
      // else if (dir & SOUTHWEST)
      //   {
      //   }
      // else if (dir & NORTH)
      //   {
      //   }
      // else if (dir & EAST)
      //   {
      //   }
      // else if (dir & SOUTH)
      //   {
      //   }
      // else if (dir & WEST)
      //   {
      //   }

      /**
       * TEST TILE CONDITIONS
       */
      if (tile->has_food)
        {
          break;
        }
      else if (tile->has_ant)
        {
          break;
        }

      if (next_selected_tile == NULL)
        {
          next_selected_tile = tile;
        }
      else
        {
          if (next_selected_tile->pheremone < tile->pheremone)
            {
              next_selected_tile = tile;
            }
        }
    }

  last_pos = current_state->pos;
}

void destroy(void)
{
  if (self != NULL)
    {
      free(self);
    }
}