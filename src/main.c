#include "engine.h"
// #include "ant.h"
// #include "tile.h"
// #include "direction.h"
// #include "statemanager.h"
#include "gametime.h"
#include "linked_list.h"
#include "gamestate.h"

#include <stdlib.h>
#include <unistd.h>

// #define MAX(x, y)   (((x) > (y)) ? (x) : (y))
// #define MIN(x, y)   (((x) < (y)) ? (x) : (y))

// #define MAP_WIDTH   100
// #define MAP_HEIGHT  100

#define SPAWN_TIMER   2000
#define FRAME_TIME_MS 30

// static int running = 1;
// static ant_t *ant  = NULL;
// static entity_state_t state;

// unsigned int init_gamestate(tile_t **tiles, camera_t *camera)
// {
//   camera->w = 80;
//   camera->h = 12;
//   // camera->x = map_width / 2 - (camera->w / 2);
//   // camera->y = map_height / 2 - (camera->h / 2);
//   camera->x = 0;
//   camera->y = 0;

//   // init map
//   for (int x = 0; x < MAP_WIDTH; x++)
//     {
//       tiles[x] = malloc(sizeof(tile_t) * MAP_HEIGHT);
//       for (int y = 0; y < MAP_HEIGHT; y++)
//         {
//           tile_init((tile_t *)&tiles[x][y]);
//         }
//     }
//   // init ants
//   ant_init(&ant, &state, 40, 12);
//   for (uint8_t i = 0; i < sizeof(state.surroundings) / sizeof(tile_t *); i++)
//     {
//       state.surroundings[i] = malloc(sizeof(tile_t));
//     }
// }

// unsigned int update_input_gamestate(int input, camera_t *camera)
// {
//   // handle input
//   if (input == KEY_LEFT)
//     {
//       camera->x = MAX(0, MIN(MAP_WIDTH - camera->w, camera->x - 1));
//     }
//   if (input == KEY_RIGHT)
//     {
//       camera->x = MAX(0, MIN(MAP_WIDTH - camera->w, camera->x + 1));
//     }
//   if (input == KEY_UP)
//     {
//       camera->y = MAX(0, MIN(MAP_HEIGHT - camera->h, camera->y - 1));
//     }
//   if (input == KEY_DOWN)
//     {
//       camera->y = MAX(0, MIN(MAP_HEIGHT - camera->h, camera->y + 1));
//     }
// }

// unsigned int update_gamestate(tile_t **map, camera_t *camera)
// {

//   ant_update(ant, &state);
//   /**
//    * CALCULATE DIRECTION
//    */
//   if (ant->dir & NORTH)
//     {
//       state.pos.y--;
//     }
//   if (ant->dir & EAST)
//     {
//       state.pos.x++;
//     }
//   if (ant->dir & SOUTH)
//     {
//       state.pos.y++;
//     }
//   if (ant->dir & WEST)
//     {
//       state.pos.x--;
//     }
// }

// unsigned int draw_gamestate(tile_t **map, camera_t *camera)
// {
//   clear();
//   // iterate over map
//   for (int y = 0; y < camera->h; y++)
//     {
//       for (int x = 0; x < camera->w; x++)
//         {
//           // char tile = '.'; //tile_render(map[camera->x + x][camera->y + y]);
//           char tile = tile_render((tile_t)map[camera->x + x][camera->y + y]);
//           mvaddch(y, x, tile);
//         }
//     }
//   if(state.pos.y >= camera->y && state.pos.y <= camera->y + camera->h && state.pos.x >= camera->x && state.pos.x <= camera->x + camera->w)
//   {
//     mvaddch(state.pos.y - camera->y, state.pos.x - camera->x, '@');
//   }

//   // mvaddch(state.pos.y, state.pos.x, '@');
//   //  render some debug info
// }

int main()
{
  engine_init();

  bool running = true;
  int input;

  refresh();

  float msec        = 0.0;
  float frame_timer = 0.0;

  // init_gamestate(tiles, camera);
  gamestate_init();
  clock_t before = clock();

  while (running)
    {
      clock_t delta = clock() - before;
      msec          = (float)(delta * 1000) / CLOCKS_PER_SEC;

      erase();
      gamestate_update(msec);
      gamestate_draw(msec);

      before = clock();
      refresh();
      usleep(FRAME_TIME_MS * 1000);
      refresh();
      usleep(FRAME_TIME_MS * 1000);
    }

  endwin();
  return 0;
}