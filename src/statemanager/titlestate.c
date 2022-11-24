#include "titlestate.h"

#define GAME_TITLE "Ant Simulator"
#define PROMPT     "Press any key to begin"

//#define ART_FILEPATH  "../../assets/title.art"

static int title_pressed = FALSE;

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
  int title_x = (COLS / 2) - (strlen(GAME_TITLE) / 2);
  int title_y = (LINES / 3);
  mvprintw(title_y, title_x, GAME_TITLE);
  int prompt_x = (COLS / 2) - (strlen(PROMPT) / 2);
  int prompt_y = (LINES / 2);
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