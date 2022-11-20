#include "engine.h"
#include "ant.h"
#include "direction.h"
#include "statemanager.h"
#include "gametime.h"
//#include <time.h>
#include <stdlib.h>

#define SPAWN_TIMER 2000
#define FRAME_TIME 500

static int running = 1;
static ant_t *ant = NULL;
static entity_state_t state;

unsigned int init_gamestate()
{
  ant_init(&ant, &state);
}

unsigned int update_gamestate(float dt)
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

unsigned int draw_gamestate(float dt)
{
  clear();
  // iterate over map
  for (int y = 0; y < LINES - 1; y++)
    {
      for (int x = 0; x < COLS - 1; x++)
        {
          mvaddch(y, x, '.');
        }
    }
  mvaddch(state.pos.y, state.pos.x, '@');
  // render some debug info
}

int main()
{
  engine_init();

  int input;
  int maxlines = LINES - 1;
  int maxcols  = COLS - 1;

  refresh();

  clock_t msec  = 0;
  clock_t spawn_timer = 0;

  init_gamestate();
  clock_t before = clock();

  while (running)
    {
      // input = getch();
      // if (input == KEY_BACKSPACE)
      //   {
      //     return 0;
      //   }
      clock_t delta = clock() - before;
      msec = (clock_t)delta * 1000 / CLOCKS_PER_SEC;
      //spawn_timer +=
      if (msec > FRAME_TIME)
        {
          clear();
          update_gamestate(delta);
          draw_gamestate(delta);
          mvprintw(0, 0, "%d", msec);
          before = clock();
        }
      // mvprintw(0, 0, "%ull", delta);
      refresh();
    }

  curs_set(0);
  endwin();
  return 0;
}