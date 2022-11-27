#include "engine.h"
#include "gametime.h"
#include "linked_list.h"
#include "gamestate.h"
#include "titlestate.h"
#include "statemanager.h"

#include <stdlib.h>
#include <unistd.h>

#define FRAME_TIME_MS 30

static int running = 1;

int main()
{
  engine_init();

  int input;
  scene_t scene_result;
  State* current_scene;

  StateManager statemanager;
  sm_init(&statemanager);

  State gamestate = {0};
  gamestate.init = gamestate_init;
  gamestate.update = gamestate_update;
  gamestate.draw = gamestate_draw;
  gamestate.destroy = gamestate_destroy;
  
  State titlestate = {0};
  titlestate.init = titlestate_init;
  titlestate.update = titlestate_update;
  titlestate.draw = titlestate_draw;
  titlestate.destroy = titlestate_destroy;

  refresh();

  float msec        = 0.0;
  //float frame_timer = 0.0;

  //gamestate_init();
  sm_push(&statemanager, &titlestate);
  current_scene = sm_top(&statemanager);

  clock_t before = clock();

  while (running)
    {
      clock_t delta = clock() - before;
      msec          = (float)(delta * 1000) / CLOCKS_PER_SEC;
      input = getch();
      //gamestate_update(msec);
      scene_result = sm_update(&statemanager, msec, input);
      if(scene_result != SCENE_OKAY)
      {
        if(scene_result == SCENE_GAME)
        {
          if(current_scene == &titlestate)
          {
            sm_push(&statemanager, &gamestate);
            current_scene = sm_top(&statemanager);
          }
          else
          {
            sm_pop(&statemanager);
            current_scene = sm_top(&statemanager);
          }
        }
      }
      //gamestate_draw(msec);
      sm_draw(&statemanager, msec);
      before = clock();
      refresh();
      usleep(FRAME_TIME_MS);
    }

  endwin();
  return 0;
}