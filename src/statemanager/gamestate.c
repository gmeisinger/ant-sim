#include "gamestate.h"

#define MAX(x, y)   (((x) > (y)) ? (x) : (y))
#define MIN(x, y)   (((x) < (y)) ? (x) : (y))

#define SPAWN_TIMER 2000
#define GAME_TICK   .05

static int running        = 1;
static float update_timer = 0.0;
static ant_t *ant         = NULL;

static camera_t *camera;
static tile_t **tiles;
static llist_t *ant_list;
// static tile_t *tiles[MAP_WIDTH][MAP_HEIGHT];

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
          ant->surroundings[j] = (below(y, 0) || above(x, MAP_WIDTH)) ? NULL : &tiles[x][y];
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
          ant->surroundings[j] = (above(x, MAP_WIDTH)) ? NULL : &tiles[x][y];
          ant->dir |= ((ant->surroundings[j] != NULL) << 4); // EAST is valid
        }
      else if (j == 6)
        {
          y += 1;
          x -= !x ? 0 : 1;
          ant->surroundings[j] = (above(y, MAP_HEIGHT) || below(x, 0)) ? NULL : &tiles[x][y];
        }
      else if (j == 7)
        {
          y += 1;
          ant->surroundings[j] = (above(y, MAP_HEIGHT)) ? NULL : &tiles[x][y];
          ant->dir |= ((ant->surroundings[j] != NULL) << 5); // SOUTH is valid
        }
      else if (j == 8)
        {
          y += 1;
          x += 1;
          ant->surroundings[j] = (above(y, MAP_HEIGHT) || above(x, MAP_WIDTH)) ? NULL : &tiles[x][y];
        }
    }
}

unsigned int gamestate_init()
{
  /**
   * INIT RANDOMNESS
   */
  time_t t;
  srand((unsigned)time(&t));

  /**
   * INIT 2D TILES ARRAY
   */
  // tiles = malloc(sizeof(tile_t **) * MAP_WIDTH);
  // for (int x = 0; x < MAP_WIDTH; x++)
  //   {
  //     tiles[x] = malloc(sizeof(tile_t *) * MAP_HEIGHT);
  //     for (int y = 0; y < MAP_HEIGHT; y++)
  //       {
  //         tile_init((tile_t *)&tiles[x][y]);
  //       }
  //   }

  tiles = malloc(sizeof(tile_t *));   // Create `tile_t**`
  for (int x = 0; x < MAP_WIDTH; x++) // For `max width`
    {
      // Create a column of tiles, of size `max height`
      tiles[x] = malloc(sizeof(tile_t) * MAP_HEIGHT);
      for (int y = 0; y < MAP_HEIGHT; y++)
        {
          tile_init(&tiles[x][y]);
        }
    }

  /**
   * INIT CAMERA
   */
  camera = malloc(sizeof(camera_t));

  camera->w = 80;
  camera->h = 24;
  camera->x = 0;
  camera->y = 0;

#define ANT_COUNT 10
  /**
   * INIT ANTS
   */
  llist_create(&ant_list); // Init linked list handle for ants
  ant_t ants[ANT_COUNT];   // Create ant structs
  for (int i = 0; i < ANT_COUNT; i++)
    {
      ant_t *ant = &ants[i];
      ant_init(&ant, 80 / 2, 24 / 2);   // Initialize ant
      set_ant_surroundings(ant, tiles); // Provide adjacent tiles to ant
      llist_add(ant_list, ant);         // Add to end of list
    }
}
unsigned int gamestate_update_input(int input)
{
  // handle input
  if (input == KEY_LEFT)
    {
      camera->x = MAX(0, MIN(MAP_WIDTH - camera->w, camera->x - 1));
    }
  if (input == KEY_RIGHT)
    {
      camera->x = MAX(0, MIN(MAP_WIDTH - camera->w, camera->x + 1));
    }
  if (input == KEY_UP)
    {
      camera->y = MAX(0, MIN(MAP_HEIGHT - camera->h, camera->y - 1));
    }
  if (input == KEY_DOWN)
    {
      camera->y = MAX(0, MIN(MAP_HEIGHT - camera->h, camera->y + 1));
    }
}
unsigned int gamestate_update_state()
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
          ant->pos.x += ant->pos.x >= MAP_WIDTH - 1 ? 0 : 1;
        }
      if (ant->dir & SOUTH)
        {
          ant->pos.y += ant->pos.y >= MAP_HEIGHT - 1 ? 0 : 1;
        }
      if (ant->dir & WEST)
        {
          ant->pos.x -= !ant->pos.x ? 0 : 1;
        }
      set_ant_surroundings(ant, tiles); // Set new adjacent tiles
      ant_update(ant);                  // Handle ant update
    }
}
unsigned int gamestate_draw(float delta)
{
  clear();
  // iterate over map
  for (int y = 0; y < camera->h; y++)
    {
      for (int x = 0; x < camera->w; x++)
        {
          // char tile = '.'; // tile_render(map[camera->x + x][camera->y + y]);
          char tile = tile_render(tiles[camera->x + x][camera->y + y]);
          mvaddch(y, x, tile);
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
      if (ant->pos.y >= camera->y && ant->pos.y <= camera->y + camera->h && ant->pos.x >= camera->x && ant->pos.x <= camera->x + camera->w)
        {
          mvaddch(ant->pos.y - camera->y, ant->pos.x - camera->x, '@');
        }
    }
}

unsigned int gamestate_update(float delta)
{
  update_timer += delta;
  int input = getch();
  gamestate_update_input(input);
  if (update_timer > GAME_TICK)
    {
      update_timer = 0.0;
      gamestate_update_state();
    }
}