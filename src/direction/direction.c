#include "direction.h"
#include <stdlib.h>
#include <time.h>

static uint8_t generate_random_4bit(void)
{
  uint8_t bit1  = rand() % 2;
  uint8_t bit2  = rand() % 2;
  uint8_t shift = (rand() % 4) + 1;

  uint8_t start_dir = (bit1 << shift) | (bit2 << (shift - 1));

  start_dir |= (start_dir >> 4);
  return start_dir &= 0x0F;
}
void init_direction(uint8_t *dir)
{
  *dir = generate_random_4bit();
}

void next_direction(uint8_t *dir)
{
  uint8_t next_dir;
  do
    {
      next_dir = generate_random_4bit();
      next_dir = ((*dir >> 4) & next_dir);
    }
  while (!next_dir && (*dir & 0xF0));
  *dir = next_dir | (*dir & 0xF0);
  // *dir = ((*dir >> 4) & next_dir) | (*dir & 0xF0);
}