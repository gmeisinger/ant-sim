#include "tile.h"
#include <stdlib.h>
#include <time.h>

int tile_init(tile_t *tile)
{
  tile->has_ant = false;
  tile->has_food = false;
  tile->pheremone = 0;
  int roll = rand() % 100;
  if(roll <= 2)
  {
    tile->has_food = true;
  }
  return 0;
}

char tile_render(tile_t *tile)
{
  if(tile->pheremone > 10)
  {
    return 'p';
  }
  else if (tile->has_food)
  {
    return 'F';
  }
  else return ' ';
}