#include "mainmenu.h"
#include "state.h"
#include "player.h"
#include "instructions.h"

MainMenu::MainMenu(){
  current = LOAD_GAME;
}

void MainMenu::Draw(){
  io::printMsg("Load Game", 32, 16, 15, (current == LOAD_GAME) ? Green : Grey);
  io::printMsg("Create New Character", 32, 18, 30, (current == CREATE_NEW) ? Green: Grey);
  io::printMsg("Help", 32, 20, 30, (current == HELP) ? Green: Grey);
  io::printMsg("Quit", 32, 22, 30, (current == QUIT) ? Green: Grey);
  
  io::flip();
}

void MainMenu::Update(){
  // newPlayerState

  std::unique_ptr<State> CreatePlayerState(new newPlayer());
  std::unique_ptr<State> InstructionState(new instrState());
  // Handle menu navigation
  Keys key = io::Input();
  switch(key){
  case E_QUIT:
    states::pop();
    break;

  case K_UP:
    switch(current){
    case LOAD_GAME:
      current = QUIT;
      break;
    case CREATE_NEW:
      current = LOAD_GAME;
      break;
    case HELP:
      current = CREATE_NEW;
      break;
    case QUIT:
      current = HELP;
      break;
    default:
      break;
     }    
    break;
    
  case K_DOWN:
    switch(current){
    case LOAD_GAME:
      current = CREATE_NEW;
      break;
    case CREATE_NEW:
      current = HELP;
      break;
    case HELP:
      current = QUIT;
      break;
    case QUIT:
      current = LOAD_GAME;
      break;
    default:
      break;
    }
    break;
    
  case K_RETURN:
    switch(current){
    case LOAD_GAME:
      
      break;
    case CREATE_NEW:
 
      states::push(std::move(CreatePlayerState));    
      break;
    case HELP:
      states::push(std::move(InstructionState));
      break;
    case QUIT:
      states::pop();
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
    
}
