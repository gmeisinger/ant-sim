#ifndef _TITLESTATE_H_
#define _TITLESTATE_H_

#include "engine.h"
#include "gametime.h"
#include "linked_list.h"
#include "scene.h"

#include <stdlib.h>
#include <string.h>

unsigned int titlestate_init();
unsigned int titlestate_update_input(int input);
unsigned int titlestate_update_state();
unsigned int titlestate_draw(float delta);
unsigned int titlestate_update(float delta, int input);
unsigned int titlestate_destroy();

#endif