#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

//#include "state.h"

typedef unsigned int (*fnPtr)();
typedef unsigned int (*fnPtrFl)(float);

typedef struct
{
  fnPtr init;
  fnPtrFl update;
  fnPtrFl draw;
  fnPtr destroy;
} State;

typedef struct
{
  State **stack;
  int capacity;
  int top;
} StateManager;

int sm_init(StateManager *statemanager);
int sm_free(StateManager *statemanager);
int sm_push(StateManager *statemanager, State *state);
int sm_pop(StateManager *statemanager);
State *sm_top(StateManager *statemanager);
int sm_update(StateManager *statemanager, float deltatime);
int sm_draw(StateManager *statemanager, float deltatime);

#endif