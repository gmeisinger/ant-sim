#ifndef state_h
#define state_h

typedef unsigned int (*fnPtr)();
typedef unsigned int (*fnPtrFl)(float);

typedef struct
{
  fnPtr init;
  fnPtrFl update;
  fnPtrFl draw;
  fnPtr destroy;
} State;