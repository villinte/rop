#ifndef GAME_H
#define GAME_H

#include "state.h"

class Entity;
class Fighter;
class Mortal;
class Actor;

namespace Game{

  extern bool isRunning;
  extern unsigned int turnCounter;
  extern unsigned int healCounter;

  // player movement
  extern int p_dx;
  extern int p_dy;

    
  extern std::unique_ptr<Entity> player;
  extern std::vector<std::unique_ptr<Entity>> actors;
  
  void Init();

  void Cleanup();

  void Render();

  void Tick();

  void handleInput();
  
  void newTurn();

  void clearActors();
  
}


class GameState : public State{

 public:
  GameState();
  void Init() override;
  void Draw() override;
  void Update() override;
  
};


#endif
