#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

class sdlEngine;
class Entity;
class Mortal;
class Fighter;
class Ai;

namespace Game{
  
  extern bool isRunning;
  extern sdlEngine sdl;
  extern unsigned int turnCounter;
  extern unsigned int healCounter;

  extern std::unique_ptr<Entity> player;
  
  extern std::vector<std::unique_ptr<Entity>> actors;
  void Init();
  
  // -- Handles player creation etc.
  void runStartMenu();  
  
  void runGame();

  void Render();
  
  void Input();
  
  void Tick();

  void newTurn();

  void menuState();

  void clearActors();
  
}

#endif
