#include <stdint.h>

#define NORTH     (1 << 3)
#define EAST      (1 << 2)
#define SOUTH     (1 << 1)
#define WEST      (1 << 0)
#define NORTHEAST (NORTH | EAST)
#define NORTHWEST (NORTH | WEST)
#define SOUTHEAST (SOUTH | EAST)
#define SOUTHWEST (SOUTH | WEST)

uint8_t init_direction(void);

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
