#ifndef gamestate_h
#define gamestate_h

#include "../data_structures/linked_list.h"

#include "statemanager.h"
#include "../entities/ant/ant.h"

typedef struct
{
  llist_t *ants;
  State *state;
} gamestate_t;

int gamestate_init(gamestate_t *gamestate);
int gamestate_update(gamestate_t *gamestate, float delta);

#endif