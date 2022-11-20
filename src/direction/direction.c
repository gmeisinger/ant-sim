#include "direction.h"
#include <stdlib.h>
#include <time.h>

uint8_t init_direction(void)
{
  /**
   * Calculate random direction, for passing into the `init` state
   */
  time_t t;
  srand((unsigned) time(&t));
  
  // either cardinal dir, or compound(?) dir.
  uint8_t start_dir = (rand() & 8);  // 0 - 3
  if(start_dir >= 5)
  {
    start_dir++;
  }

  return start_dir;
}