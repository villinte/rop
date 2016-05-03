#include "game.h"
#include <iostream>
#include "sdl_wrapper.h"
#include "actor.h"
#include "feature_ai.h"
#include "map.h"


Game::Game(){
  player = new Actor(16,24, "Player",'@', White);
  player->ai = new PlayerAi();
  actors.push_back(player);
  
  isRunning = true;
}

Game::~Game(){
  for (std::vector< Actor* >::iterator it = actors.begin() ; it != actors.end(); ++it){
    delete (*it);
  } 
  actors.clear();
}

void Game::Render(){
  engine.clear();
  
  map.Render();

  player->Render();
  
  engine.flip();
}

void Game::Update(){
  player->Update();
}
