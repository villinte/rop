#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include "globals.h"

class Ai;
class Actor {
 public:
  Actor(int x, int y, std::string name, char glyph, cColor c);
  ~Actor();
  
  void Update();
  void Render();

  void setX(int x) { _x = x; }
  void setY(int y) { _y = y; }
  int getX() { return _x; }
  int getY() { return _y; }

  Ai *ai;
  
 private:
  int _x;
  int _y;
  std::string _name;
  char _glyph;
  cColor _color;
  bool _block;
};
#endif
