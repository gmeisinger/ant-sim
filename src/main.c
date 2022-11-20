#include "engine.h"
#include "statemanager.h"
#include "gametime.h"
#include <stdlib.h>

static int running = 1;

unsigned int init_gamestate()
{
  return 0;
}

unsigned int update_gamestate(float dt)
{
}

unsigned int draw_gamestate(float dt)
{
  // render some debug info
  mvprintw(maxlines, 0, "%.6f", dt);
}

int main()
{
  engine_init();

  int input;
  int maxlines = LINES - 1;
  int maxcols  = COLS - 1;

  StateManager statemanager;

  State gamestate = {0};

  refresh();

  int msec = 0, trigger = 1000; /* 10ms */
  clock_t before = clock();

  init_gamestate();

  while (running)
    {
      clock_t delta = clock() - before;
      msec          = delta * 1000 / CLOCKS_PER_SEC;
      if (msec > trigger)
        {
          msec = 0;
          update_gamestate(delta * 1000);
          draw_gamestate(delta * 1000);
        }
      refresh();
    }

  curs_set(0);
  endwin();
  return 0;
}