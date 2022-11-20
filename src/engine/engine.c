#include "engine.h"

int engine_init()
{
  // Engine* engine = malloc(sizeof(Engine));

  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr, true);
  nodelay(stdscr, true);

  clear();
  refresh();
}

engine_exit()
{
  endwin();
}