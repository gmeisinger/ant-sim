#include "titlestate.h"

#define GAME_TITLE "Ant Simulator"
#define PROMPT     "Press any key to begin"

//#define ART_FILEPATH  "../../assets/title.art"

#define TITLE_LINES 8
const char *TITLE_ART[TITLE_LINES] = {
  " ________  ________   _________        ________  ___  _____ ______      ",
  "|\\   __  \\|\\   ___  \\|\\___   ___\\     |\\   ____\\|\\  \\|\\   _ \\  _   \\    ",
  "\\ \\  \\|\\  \\ \\  \\\\ \\  \\|___ \\  \\_|     \\ \\  \\___|\\ \\  \\ \\  \\\\\\__\\ \\  \\   ",
  " \\ \\   __  \\ \\  \\\\ \\  \\   \\ \\  \\       \\ \\_____  \\ \\  \\ \\  \\\\|__| \\  \\  ",
  "  \\ \\  \\ \\  \\ \\  \\\\ \\  \\   \\ \\  \\       \\|____|\\  \\ \\  \\ \\  \\    \\ \\  \\ ",
  "   \\ \\__\\ \\__\\ \\__\\\\ \\__\\   \\ \\__\\        ____\\_\\  \\ \\__\\ \\__\\    \\ \\__\\",
  "    \\|__|\\|__|\\|__| \\|__|    \\|__|       |\\_________\\|__|\\|__|     \\|__|",
  "                                         \\|_________|                   ",
};

int title_pressed = FALSE;

unsigned int titlestate_init()
{
  //erase();
  return 0;
}

unsigned int titlestate_update_input(int input)
{
  if (input != -1)
    {
      return TRUE;
    }
  return FALSE;
}

unsigned int titlestate_update_state()
{
  return 0;
}

unsigned int titlestate_draw(float delta)
{
  // int title_x = (COLS / 2) - (strlen(GAME_TITLE) / 2);
  // int title_y = (LINES / 3);
  int title_x = (COLS / 2) - (strlen(TITLE_ART[0]) / 2);
  int title_y = (LINES / 4);
  for(int i=0;i<TITLE_LINES;i++)
  {
    mvprintw(title_y+i, title_x, TITLE_ART[i]);
  }
  //mvprintw(0,0, TITLE_ART);
  int prompt_x = (COLS / 2) - (strlen(PROMPT) / 2);
  int prompt_y = LINES - (LINES / 3);
  mvprintw(prompt_y, prompt_x, PROMPT);
  if (title_pressed)
    {
      int go_x = (COLS / 2) - (strlen("GO!!") / 2);
      int go_y = (LINES / 2);
      mvprintw(go_y, go_x, "GO!!");
    }
    return 0;
}

unsigned int titlestate_update(float delta, int input)
{
  uint8_t title_pressed = titlestate_update_input(input);
  if(title_pressed)
  {
    //return a value that pushes a scene on the stack
    return SCENE_GAME;
  }
  return SCENE_OKAY;
}

unsigned int titlestate_destroy()
{
  return 0;
}