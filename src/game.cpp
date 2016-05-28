#include "game.h"
#include <iostream>
#include "sdl_wrapper.h"
#include "actor.h"
#include "feature_ai.h"
#include "map.h"
#include "gui.h"

Game::Game(){
  player = new Actor(1,1, "Player",'@', White);
  player->ai = new PlayerAi();
  actors.push_back(player);
  Map::cleanMap();
  Map::createMap();
  Gui::LogMsg("hej");

  isRunning = true;
}

Game::~Game(){
  for (std::deque< Actor* >::iterator it = actors.begin() ; it != actors.end(); ++it){
    delete (*it);
  } 
  actors.clear();
}

void Game::Render(){
  engine.clear();
  
  Map::renderMap();
  player->Render();
  Gui::RenderGui();
  engine.flip();
}

void Game::Update(){
  player->Update();
}
