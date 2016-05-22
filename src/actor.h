#ifndef ACTOR_H
#define ACTOR_H
#include <string>
#include "globals.h"
#include "helper.h"
class P;
class Ai;
class Actor {
 public:
  Actor(int x, int y, std::string name, char glyph, cColor c);
  ~Actor();
  
  void Update();
  void Render();

  Ai *ai;
  P pos;
 private:
  int _x;
  int _y;
  std::string _name;
  char _glyph;
  cColor _color;
  bool _block;
};
#endif
