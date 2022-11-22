#include "engine.h"

int engine_init()
{
  // Engine* engine = malloc(sizeof(Engine));

  initscr();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
  noecho();
  //timeout(-1);

  clear();
  refresh();
}

engine_exit()
{
  endwin();
}
