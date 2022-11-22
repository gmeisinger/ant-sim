#include "ant.h"
#include "direction.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define CURRENT_TILE_INDEX 4 /* from zero */

void ant_init(ant_t **ant, int x, int y)
{
  *ant          = malloc(sizeof(ant_t));
  (*ant)->pos.x = x;
  (*ant)->pos.y = y;
  init_direction(&(*ant)->dir);
}

void ant_update(ant_t *ant)
{
  static uint8_t valid_tiles;
  tile_t *next_selected_tile = NULL;
  // int max_pheremone = 0;

  for (unsigned i = 0; i < sizeof(ant->surroundings) / sizeof(tile_t *); i++)
    {
      tile_t *tile = ant->surroundings[i];
      if (tile == NULL)
        {
          valid_tiles &= ~(1 << i);
          continue;
        }

      if (i == CURRENT_TILE_INDEX)
        {
          // if (tile->has_food)
          //   {
          //     tile->has_food = false;
          //     ant->has_food  = true;
          //     break;
          //   }
          // if (tile->has_ant)
          //   {
          //     // TODO: finish
          //     break;
          //   }
        }
      else
        {
          valid_tiles |= (1 << i);

          /**
           * TEST TILE CONDITIONS
           */
          // if (tile->has_food)
          //   {
          //     next_selected_tile = tile;
          //     break;
          //   }
          // else if (tile->has_ant)
          //   {
          //     // TODO: finish
          //     break;
          //   }
          // else
          //   {
          // /**
          //  * CALCULATE NEW TILE BASED ON PHEREMONE LEVEL
          //  */
          // if (next_selected_tile == NULL)
          //   {
          //     next_selected_tile = tile;
          //   }
          // else
          //   {
          //     if (next_selected_tile->pheremone < tile->pheremone)
          //       {
          //         next_selected_tile = tile;
          //       }
          //   }
          // }
        }

      if (next_selected_tile == NULL)
        {
          /**
           * CALCULATE NEW TILE BASED ON PHEREMONE LEVEL
           */
          // if (next)
        }
      ant->dir |= (valid_tiles << 4);
      next_direction(&ant->dir);
    }
}

void ant_destroy(ant_t **ant)
{
  if (*ant != NULL)
    {
      free(*ant);
    }
  *ant = NULL;
}