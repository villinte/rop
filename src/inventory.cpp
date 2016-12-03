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
#include "gui.h"

/*
 * Boundaries for inventory window
 */
const int start_x = globals::SCREEN_WIDTH/2;
const int start_y = 0;
const int end_x   = globals::SCREEN_WIDTH;
const int end_y   = globals::SCREEN_HEIGHT;

/*
 * Boundaries for text within window
 */
const int t_x = globals::MAP_WIDTH/2+2;
const int t_y = 3;


InventoryState::InventoryState(){

}

void InventoryState::Init(){
  Game::player->container->inv.shrink_to_fit();
  selected = 0;
  amountItems = Game::player->container->inv.size();
}

void InventoryState::Draw(){
  SDL_Rect rect = {start_x, start_y, end_x, end_y};
  io::drawSquare(rect, Black);
  std::string temp = "Browsing Inventory";
  io::printMsg(temp, t_x+1, 1, temp.length(), Green);

  for(unsigned i = 0; i < Game::player->container->inv.size(); ++i){
    std::string name = Game::player->container->inv[i]->_name;
    
    io::printMsg(name, t_x+2, t_y+i, name.length(), Pink);
    
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
