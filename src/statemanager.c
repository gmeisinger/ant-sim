#include "./include/statemanager.h"
#include <stdlib.h>

int sm_scale(StateManager *statemanager) {
  statemanager->capacity *= 2;
  statemanager->stack = realloc(statemanager->stack, statemanager->capacity * sizeof(State*));
  return statemanager->capacity;
}

int sm_init(StateManager *statemanager) {
  statemanager->capacity = 3;
  statemanager->stack = malloc(statemanager->capacity * sizeof(State*));
  statemanager->top = -1;
  return 0;
}

int sm_free(StateManager *statemanager) {
  do {
    sm_pop(statemanager);
  } while (statemanager->top > -1);
  free(statemanager->stack);
  return 0;
}

int sm_push(StateManager *statemanager, State *state) {
  if (statemanager->top == -1) return 0;
  State *top = sm_top(statemanager);
  if(top->destroy != NULL) top->destroy();
  statemanager->stack[statemanager->top] = NULL;
  statemanager->top--;
  return statemanager->top;
}

int sm_pop(StateManager *statemanager) {
  if (statemanager -> top == -1) return 0;
  State *top = sm_top(statemanager);
  if (top -> destroy != NULL) top -> destroy();
  statemanager -> stack[statemanager -> top] = NULL;
  statemanager -> top--;
  return statemanager -> top;
}

State *sm_top(StateManager *statemanager) {
  return statemanager->stack[statemanager->top];
}

int sm_update(StateManager *statemanager, float deltatime) {
  State *state = sm_top(statemanager);
  if(state->update != NULL) return state->update(deltatime);
  return 1;
}

int sm_draw(StateManager *statemanager, float deltatime) {
  State *state = sm_top(statemanager);
  if(state->draw != NULL) return state->draw(deltatime);
  return 1;
}