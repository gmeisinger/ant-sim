#include "./include/engine.h"
#include "./include/statemanager.h"
#include <stdlib.h>

int main() {
  engine_init();

  int player_y, player_x;
  int input;
  int running = 1;
  int maxlines = LINES - 1;
  int maxcols = COLS - 1;

  player_y = maxlines / 2;
  player_x = maxcols / 2;

  mvprintw(player_y, player_x, "@");
  refresh();

  while(running)
  {
    input = getch();
    if(input == 127)
    {
      exit(0);
    }
    if(input == KEY_DOWN)
    {
      player_y += 1; 
    }
    else if(input == KEY_UP)
    {
      player_y -= 1; 
    }
    else if(input == KEY_LEFT)
    {
      player_x -= 1; 
    }
    else if(input == KEY_RIGHT)
    {
      player_x += 1; 
    }

    // render map
    for(int y=0;y<maxlines;y++)
    {
      for(int x=0;x<maxcols;x++)
      {
        mvaddch(y, x, '.');
      }
    }

    // render player
    mvprintw(player_y, player_x, "@");

    // render some debug info
    mvprintw(maxlines - 1, 0, "%d, %d", player_x, player_y);
    mvprintw(maxlines, 0, "%d", input);

    refresh();
  }

  curs_set(0);
  endwin();
  exit(0);
}