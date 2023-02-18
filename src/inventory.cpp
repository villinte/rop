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
#include <algorithm>
#include <vector>

/*
 * Boundaries for inventory window
 */
const int start_x = g::SCREEN_WIDTH/2;
const int start_y = 0;
const int end_x   = g::SCREEN_WIDTH;
const int end_y   = g::SCREEN_HEIGHT;

/*
 * Boundaries for text within window
 */
const int t_x = g::MAP_WIDTH/2+2;
const int t_y = 3;


InventoryState::InventoryState(){
  
}

void InventoryState::Init(){
  Game::player->container->inv.shrink_to_fit();
  selected = 0;
  amountItems = Game::player->container->inv.size();
   
}

void InventoryState::Draw(){
  io::clear();
  SDL_Rect rect = {start_x, start_y, end_x, end_y};
  io::drawSquare(rect, Black);
  std::string temp = "Browsing Inventory";
  io::printMsg(temp, t_x+1, 1, temp.length(), Green);

  
  for(unsigned i = 0; i < Game::player->container->inv.size(); ++i){

    std::string name = Game::player->container->inv[i]->_name;

    if(i == selected){
      io::printMsg(name, t_x+2, t_y+i, name.length(), Green);
    }
    else{   
      io::printMsg(name, t_x+2, t_y+i, name.length(), Pink);
    }
  }
  

}

void InventoryState::Update(){


  
  // Handle menu navigation
  //  Game::player->container->inv.shrink_to_fit();
  Keys key = io::Input();
  switch(key){
  case K_ESC:
    states::pop();
    break;
    
  case K_DOWN:
    if(selected >= 0 && selected < Game::player->container->inv.size()-1){
      selected++;
    }
    else{
      selected = 0;
    }
    
    break;

  case K_UP:
    
    if(selected == 0){
      selected = Game::player->container->inv.size()-1;
    }
    else{
      selected--;
    }
    
    break;
    
  case K_RETURN:
    if(!Game::player->container->inv.empty()){
      // if item is usable, new turn and pop state.
      if(Game::player->container->inv[selected]->item->Use
	 (Game::player->container->inv[selected], Game::player)){
	amountItems = Game::player->container->inv.size();
	selected = 0;
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
