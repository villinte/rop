#ifndef GAME_H
#define GAME_H
#include <string>
#include <iostream>
#include <vector>
#include "sdl_wrapper.h"
#include "map.h"
class Game{

 public:
  Game();
  ~Game();

  void Render();
  void Update();
  
  bool isRunning;

  
 private:

  Map map;
  int x;
  int y;
  
};

#endif
