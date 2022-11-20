#include "engine.h"
#include "statemanager.h"
#include "gametime.h"
//#include <time.h>
#include <stdlib.h>

static int running = 1;

unsigned int init_gamestate()
{
 mvprintw(0, 0, "%.6f", 0.6969);
}

unsigned int update_gamestate(float dt)
{
  // int input = getch();
  // if (input == KEY_BACKSPACE)
  //   {

  //     running = -1;
  //   }
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
  // render some debug info
  mvprintw(0, 0, "%.6f", dt);
}

int main(int argc, char **argv)
{
  engine_init();

  int input;
  int maxlines = LINES - 1;
  int maxcols  = COLS - 1;

  refresh();

  int msec = 0;
  int trigger = 10000; /* 100ms */

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
      // update_gamestate(delta);
      // draw_gamestate(delta);
      //msec = delta * 1000 / CLOCKS_PER_SEC;
      // if (msec > trigger)
      //   {
      //     // update_gamestate(delta);
      //     // draw_gamestate(delta);
      //     mvprintw(0, 0, "%.6f", msec);
      //     before = clock();
      //   }
      mvprintw(0, 0, "fuck c");
      refresh();
    }

  curs_set(0);
  endwin();
  return 0;
}