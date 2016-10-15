#ifndef MAP_GENERATE_H
#define MAP_GENERATE_H

#include "helper.h"
#include "globals.h"

class Entity;
class P;

namespace Map_Generator{
  void Generate();
  void fillRect(int x_start, int y_start, int h, int w, char glyph);
  _DIR getWallDir(int x, int y);

  void makeSquareRoom(int x, int y, _DIR wallDir);
  void makeCorridor(int x, int y, _DIR wallDir);
}

#endif
