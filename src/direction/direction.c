#include "direction.h"
#include <stdlib.h>

uint8_t init_direction(void)
{
  /**
   * Calculate random direction, for passing into the `init` state
   */

  // either cardinal dir, or compound(?) dir.
  uint8_t start_dir = (rand() & 2) + 1; // 1 - 2

  // random 4-bit shift the random direction.
  uint8_t shift = rand() % 4; // 0 - 3
  start_dir <<= shift;
}