#include "game.h"

#include "globals.h"
#include "sdl_wrapper.h"

#include "map.h"

#include "entity.h"
#include "f_fighter.h"
#include "f_mortal.h"
#include "f_actor.h"
#include "f_container.h"

#include "gui.h"
#include "inventory.h"
#include "menustate.h"

namespace Game{

  bool isRunning = false;
  unsigned int turnCounter = 0;
  unsigned int healCounter = 0;
  
  // player movement
  int p_dx = 0;
  int p_dy = 0;

  std::unique_ptr<Entity> player = nullptr;
  std::vector<std::unique_ptr<Entity>> actors;

  void Init(){
    Map::Init();
    Map::cleanMap();
    Map::createMap();
    
    isRunning = true;

 
    
  }

  void Cleanup(){

  }

  void Render(){
    
    Map::renderMap();

    // Render actors
    for(auto& a : actors){
      if(Map::cells[a->pos.x][a->pos.y].isSeen)
	a->Render();
    }
    
    if(player != nullptr)
      player->Render();

    Gui::RenderGui();
    
  }

  void Tick(){
    // if death, pop all states.
    // Fix this, some kind of death state is needed

    if(!isRunning){
      states::popAll();
    }

    handleInput();
    player->Update();
    
    for(auto& a : actors){
      if(a->act){
	while(a->act->energy >= g::TURN_COST && !a->mortal->isDead()){
	  a->Update();
	}
      }
    }
    
    
  }

  void newTurn(){
    player->act->newTurn();
    for(auto& a : actors){
      if(a->act)
	a->act->newTurn();
    }
    turnCounter++;
    healCounter++;
    if(healCounter >= 20){
      player->mortal->Heal(1);
      healCounter = 0;
    }
  }

  void handleInput(){

    // Player movement varibles.
    p_dx = 0;
    p_dy = 0;

    std::unique_ptr<State> inventoryState(new InventoryState());
    std::unique_ptr<State> menuState(new MenuState());
 
    Keys key = io::Input();
    switch(key){
    case K_KP_5:
      for(int i = 0; i < 5; i++){
	if(player->act->monsterInFov()){
	  Gui::LogMsg("Monster in sight.");
	}
	else{
	  newTurn();
	}
      }
      break;
    case K_UP:
      p_dy = -1;
      break;
    case K_DOWN:
      p_dy = 1;
      break;
    case K_RIGHT:
      p_dx = 1;
      break;
    case K_LEFT:
      p_dx = -1;
      break;
    case K_HOME:
      p_dx = -1;
      p_dy = -1;
      break;
    case K_PGUP:
      p_dx = 1;
      p_dy = -1;
      break;
    case K_PGDN:
      p_dx = 1;
      p_dy = 1;
      break;
    case K_END:
      p_dx = -1;
      p_dy = 1;
      break;
    case K_KP_7:
      p_dx = -1;
      p_dy = -1;
      break;
    case K_KP_9:
      p_dx = 1;
      p_dy = -1;
      break;
    case K_KP_3:
      p_dx = 1;
      p_dy = 1;
      break;
    case K_KP_1:
      p_dx = -1;
      p_dy = 1;
      break;	      
    case E_QUIT:
      isRunning = false;
      break;
    case K_q:
      isRunning = false;
      break;
    case K_c:
      if(Map::closeDoor(player->pos))
	newTurn();
      break;
    case K_ESC:
      states::push(std::move(menuState));
      break;
    case K_l:
      Gui::showMsgLog();
      break;
    case K_i:
      states::push(std::move(inventoryState));
      break;
    case K_v:
      Gui::viewMode();
      break;
    case K_g:
      {
	for(auto &e : Game::actors){
	  if(e->item && e->pos.x == player->pos.x && e->pos.y == player->pos.y){
	    if(player->container->pickUpItem(e,player)){

	      break;// Needed, don't want to iterate over changed vector
	    }
	  
	  }
	}
      }
      break;
    default:
      break;
    }

  
    
  } // handleInput

  void clearActors(){
    actors.clear();
  } // clearActors

  std::string getEntityDescription(P p){

    for(auto &e : Game::actors){
      if(e->getP().x == p.x && e->getP().y == p.y){
	return e->_description;
      }
    }
    
    return "No Entity";
  }
  
} //namespace game

GameState::GameState(){

}

void GameState::Init(){
  Game::Init();
}

void GameState::Draw(){
  Game::Render();
}

void GameState::Update(){
  Game::Tick();
}
