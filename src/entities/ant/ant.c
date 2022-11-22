#include "ant.h"
#include "direction.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define CURRENT_TILE_INDEX 5 /* from zero */

void ant_init(ant_t **ant, entity_state_t *state, int x, int y)
{
  *ant         = malloc(sizeof(ant_t));
  (*ant)->dir  = init_direction();
  state->pos.x = x;
  state->pos.y = y;
}

void ant_update(ant_t *ant, entity_state_t *current_state)
{
  static uint8_t valid_tiles;
  tile_t *next_selected_tile = NULL;
  // int max_pheremone = 0;

  for (unsigned i = 0; i < sizeof(current_state->surroundings) / sizeof(tile_t *); i++)
    {
      tile_t *tile = current_state->surroundings[i];
      if (tile == NULL)
        {
          valid_tiles &= ~(1 << i);
          continue;
        }

      if (i == CURRENT_TILE_INDEX)
        {
          //&tiles[current_state->pos.x][current_state->pos.y]->pheremone += 1;
          
          //map_tile->pheremone += 1;
          if (tile->has_food)
            {
              tile->has_food = false;
              ant->has_food  = true;
              break;
            }
          if (tile->has_ant)
            {
              // TODO: finish
              break;
            }
        }
      else
        {
          valid_tiles |= (1 << i);

          /**
           * TEST TILE CONDITIONS
           */
          if (tile->has_food)
            {
              next_selected_tile = tile;
              break;
            }
          else if (tile->has_ant)
            {
              // TODO: finish
              break;
            }
          else
            {
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
              ant->dir = init_direction();
            }
        }

      if (next_selected_tile == NULL)
        {
          /**
           * CALCULATE NEW TILE BASED ON PHEREMONE LEVEL
           */
          // if (next)
        }
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