#include "gamestate.h"

#define MAX(x, y)   (((x) > (y)) ? (x) : (y))
#define MIN(x, y)   (((x) < (y)) ? (x) : (y))

#define SPAWN_TIMER 2000
#define GAME_TICK   .05

static int running = 1;
static float update_timer = 0.0;
static ant_t *ant  = NULL;
static entity_state_t state;

static camera_t *camera;
static tile_t ***tiles;
// static tile_t *tiles[MAP_WIDTH][MAP_HEIGHT];

unsigned int gamestate_init()
{
  camera = malloc(sizeof(camera_t));
  tiles = malloc(sizeof(tile_t **) * MAP_WIDTH);

  camera->w = 80;
  camera->h = 24;
  camera->x = 0;
  camera->y = 0;

  // init map
  for (int x = 0; x < MAP_WIDTH; x++)
    {
      tiles[x] = malloc(sizeof(tile_t *) * MAP_HEIGHT);
      for (int y = 0; y < MAP_HEIGHT; y++)
        {
          tile_init((tile_t *)&tiles[x][y]);
        }
    }
  // init ants
  ant_init(&ant, &state, 40, 12);
  for (uint8_t i = 0; i < sizeof(state.surroundings) / sizeof(tile_t *); i++)
    {
      state.surroundings[i] = malloc(sizeof(tile_t));
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
  ant_update(ant, &state);
  /**
   * CALCULATE DIRECTION
   */
  if (ant->dir & NORTH)
    {
      state.pos.y--;
    }
  if (ant->dir & EAST)
    {
      state.pos.x++;
    }
  if (ant->dir & SOUTH)
    {
      state.pos.y++;
    }
  if (ant->dir & WEST)
    {
      state.pos.x--;
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
          char tile = '.'; //tile_render(map[camera->x + x][camera->y + y]);
          //char tile = tile_render((tile_t)*tiles[camera->x + x][camera->y + y]);
          mvaddch(y, x, tile);
        }
    }
  if (state.pos.y >= camera->y && state.pos.y <= camera->y + camera->h && state.pos.x >= camera->x && state.pos.x <= camera->x + camera->w)
    {
      mvaddch(state.pos.y - camera->y, state.pos.x - camera->x, '@');
    }
}

unsigned int gamestate_update(float delta)
{
  update_timer += delta;
  int input = getch();
  gamestate_update_input(input);
  if(update_timer > GAME_TICK)
  {
    update_timer = 0.0;
    gamestate_update_state();
  }
}