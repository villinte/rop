#ifndef GAME_H
#define GAME_H
#include <vector>
#include <deque>
#include "map.h"
#include "globals.h"

class Actor;

class PlayerAi;

class Game{

 public:
  Game();
  ~Game();

  void Render();
  void Update();
  
  bool isRunning;
  

  std::deque<Actor*> actors;
  Actor *player;
  
};
extern Game game;

#endif
