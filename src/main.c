#include "engine.h"
#include "ant.h"
#include "tile.h"
#include "direction.h"
#include "statemanager.h"
#include "gametime.h"
#include "linked_list.h"
#include <stdlib.h>
#include <unistd.h>

#define SPAWN_TIMER   2000
#define FRAME_TIME_MS 500
int maxlines;
int maxcols;

static int running = 1;

#define ANT_COUNT 10
llist_t *ant_list = NULL;
tile_t **tiles;

static inline bool above(unsigned x, unsigned limit)
{
  return x >= limit - 1;
}
static inline bool below(unsigned x, unsigned limit)
{
  return x <= limit;
}
static void set_ant_surroundings(ant_t *ant, tile_t **tiles)
{
  ant->dir &= 0x0F;

  for (uint8_t j = 0; j < (sizeof(ant->surroundings) / sizeof(tile_t *)); j++)
    {
      unsigned x = ant->pos.x, y = ant->pos.y;

      if (j == 0)
        {
          y -= !y ? 0 : 1;
          x -= !x ? 0 : 1;
          ant->surroundings[j] = (below(y, 0) || below(x, 0)) ? NULL : &tiles[x][y];
        }
      else if (j == 1)
        {
          y -= !y ? 0 : 1;
          ant->surroundings[j] = (below(y, 0)) ? NULL : &tiles[x][y];
          ant->dir |= ((ant->surroundings[j] != NULL) << 7); // NORTH is valid
        }
      else if (j == 2)
        {
          y -= !y ? 0 : 1;
          x += 1;
          ant->surroundings[j] = (below(y, 0) || above(x, maxcols)) ? NULL : &tiles[x][y];
        }
      else if (j == 3)
        {
          x -= !x ? 0 : 1;
          ant->surroundings[j] = (below(x, 0)) ? NULL : &tiles[x][y];
          ant->dir |= ((ant->surroundings[j] != NULL) << 6); // WEST is valid
        }
      else if (j == 4)
        {
          ant->surroundings[j] = &tiles[x][y];
        }
      else if (j == 5)
        {
          x += 1;
          ant->surroundings[j] = (above(x, maxcols)) ? NULL : &tiles[x][y];
          ant->dir |= ((ant->surroundings[j] != NULL) << 4); // EAST is valid
        }
      else if (j == 6)
        {
          y += 1;
          x -= !x ? 0 : 1;
          ant->surroundings[j] = (above(y, maxlines) || below(x, 0)) ? NULL : &tiles[x][y];
        }
      else if (j == 7)
        {
          y += 1;
          ant->surroundings[j] = (above(y, maxlines)) ? NULL : &tiles[x][y];
          ant->dir |= ((ant->surroundings[j] != NULL) << 5); // SOUTH is valid
        }
      else if (j == 8)
        {
          y += 1;
          x += 1;
          ant->surroundings[j] = (above(y, maxlines) || above(x, maxcols)) ? NULL : &tiles[x][y];
        }
    }
}

void init_gamestate()
{
  /**
   * INIT RANDOMNESS
   */
  time_t t;
  srand((unsigned)time(&t));

  /**
   * INIT 2D TILES ARRAY
   */
  tiles = malloc(sizeof(tile_t *)); // Create `tile_t**`
  for (int i = 0; i < maxcols; i++) // For `max width`
    {
      // Create a column of tiles, of size `max height`
      tiles[i] = malloc(sizeof(tile_t) * maxlines);
    }

  /**
   * INIT ANTS
   */
  llist_create(&ant_list); // Init linked list handle for ants
  ant_t ants[ANT_COUNT];   // Create ant structs
  for (int i = 0; i < ANT_COUNT; i++)
    {
      ant_t *ant = &ants[i];
      ant_init(&ant, maxcols / 2, maxlines / 2); // Initialize ant
      set_ant_surroundings(ant, tiles);          // Provide adjacent tiles to ant
      llist_add(ant_list, ant);                  // Add to end of list
    }
}

void update_gamestate(void)
{
  /**
   * UPDATE ANTS
   */
  struct node *node = *ant_list;
  while (node->next != NULL) // For each ant...
    {
      ant_t *ant = (ant_t *)node->data;
      node       = node->next;

      // Calculate next position for ant
      if (ant->dir & NORTH)
        {
          ant->pos.y -= !ant->pos.y ? 0 : 1;
        }
      if (ant->dir & EAST)
        {
          ant->pos.x += ant->pos.x >= maxcols - 1 ? 0 : 1;
        }
      if (ant->dir & SOUTH)
        {
          ant->pos.y += ant->pos.y >= maxlines - 1 ? 0 : 1;
        }
      if (ant->dir & WEST)
        {
          ant->pos.x -= !ant->pos.x ? 0 : 1;
        }
      set_ant_surroundings(ant, tiles); // Set new adjacent tiles
      ant_update(ant);                  // Handle ant update
    }
}

void draw_gamestate(void)
{
  clear();

  /**
   * DRAW MAP
   */
  for (int y = 0; y < maxlines; y++)
    {
      for (int x = 0; x < maxcols; x++)
        {
          mvaddch(y, x, '.');
        }
    }

  /**
   * DRAW ANTS
   */
  struct node *node = *ant_list;
  while (node->next != NULL)
    {
      ant_t *ant = (ant_t *)node->data;
      node       = node->next;
      mvaddch(ant->pos.y, ant->pos.x, '@');
    }
}

int main()
{
  engine_init();

  maxlines = LINES;
  maxcols  = COLS;

  refresh();

  init_gamestate();

  while (running)
    {
      clear();
      update_gamestate();
      draw_gamestate();
      refresh();
      usleep(FRAME_TIME_MS * 1000);
    }

  curs_set(0);
  endwin();
  return 0;
}