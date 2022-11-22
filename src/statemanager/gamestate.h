#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

#include "engine.h"
#include "tile.h"
#include "camera.h"
#include "ant.h"
#include "direction.h"
#include "gametime.h"

#include <stdlib.h>

#define MAP_WIDTH   100
#define MAP_HEIGHT  100

unsigned int gamestate_init();
unsigned int gamestate_update_input(int input);
unsigned int gamestate_update_state();
unsigned int gamestate_draw(float delta);
unsigned int gamestate_update(float delta);

#endif