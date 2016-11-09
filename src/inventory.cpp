#include "inventory.h"
#include "f_container.h"
#include <memory>
#include <iostream>
#include "entity.h"
#include "globals.h"
#include "helper.h"
#include "game.h"
#include "sdl_wrapper.h"
#include <string>
#include "f_item.h"

InventoryState::InventoryState(){

}

void InventoryState::Init(){
  
}

void InventoryState::Draw(){
  SDL_Rect rect = {globals::SCREEN_WIDTH/2, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT};
  io::drawSquare(rect, Black);
  std::string temp = "Browsing Inventory";
  io::printMsg(temp, globals::MAP_WIDTH/2+1, 1, temp.length(), Green);

  for(unsigned i = 0; i < Game::player->container->inv.size(); ++i){
    std::string name = Game::player->container->inv[i]->_name;
    io::printMsg(name, globals::MAP_WIDTH/2+2, 3+i, name.length(), Pink);
  }
  
}

void InventoryState::Update(){
   // Handle menu navigation
  Keys key = io::Input();
  switch(key){
  case K_ESC:
    states::pop();
    break;
  case K_RETURN:
    if(!Game::player->container->inv.empty()){
      // if item is usable, new turn and pop state.
      if(Game::player->container->inv.back()->item->Use
	 (*Game::player->container->inv.back(), *Game::player)){
	Game::newTurn();
	states::pop();
      }
    }
    break;
  default:
    break;
  }
}

void InventoryState::Pause(){

}

void InventoryState::Resume(){

}

namespace Inventory{

  void Show(std::unique_ptr<Container> &c){
  }
  
}
