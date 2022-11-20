#include "direction.h"
#include <stdlib.h>
#include <time.h>

uint8_t init_direction(void)
{
  time_t t;
  srand((unsigned)time(&t));

  // either cardinal dir, or compound(?) dir.
  uint16_t start_dir = (rand() % 4) + 1; // 1 - 4
  uint16_t shift     = (rand() % 3);     // 0 - 2
  start_dir <<= shift;
  start_dir |= (start_dir >> 4);
  start_dir &= 0x0F;

  return start_dir;
}