#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

class sdlEngine;
class Entity;
class Ai;

namespace Game{
  
  extern bool isRunning;
  extern sdlEngine sdl;

  extern std::unique_ptr<Entity> player;
  
  extern std::vector<std::unique_ptr<Entity>> actors;
  void Init();
  
  // -- Handles player creation etc.
  void runStartMenu();   
  
  void runGame();

  void Render();
  
  void Input();
  
  void Tick();

  void menuState();
  
}

#endif
