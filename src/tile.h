#ifndef _TILE_H_
#define _TILE_H_

typedef struct
{
  pheremone_level_t pheremone;
  bool has_ant;
  enum food has_food;
} tile_t;

#endif /* _TILE_H_ */