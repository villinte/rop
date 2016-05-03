#ifndef GAME_H
#define GAME_H
#include <vector>
#include "map.h"
class Actor;

class PlayerAi;

class Game{

 public:
  Game();
  ~Game();

  void Render();
  void Update();
  
  bool isRunning;

  Map map;
  std::vector<Actor*> actors;
  Actor *player;
};
extern Game game;

#endif
