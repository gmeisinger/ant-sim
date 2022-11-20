#include "gamestate.h"

int gamestate_update(gamestate_t *gamestate, float delta)
{
}

int gamestate_draw()
{
}

int gamestate_init(gamestate_t *gamestate)
{
  state->update = gamestate_update;
  state->draw   = gamestate_draw;
}