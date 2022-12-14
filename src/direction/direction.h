#include <stdint.h>

#define NORTH     (1 << 3)
#define EAST      (1 << 2)
#define SOUTH     (1 << 1)
#define WEST      (1 << 0)
#define NORTHEAST (NORTH | EAST)
#define NORTHWEST (NORTH | WEST)
#define SOUTHEAST (SOUTH | EAST)
#define SOUTHWEST (SOUTH | WEST)

/**
 * Calculate random initial direction
 */
void init_direction(uint8_t *dir);

void next_direction(uint8_t *dir);