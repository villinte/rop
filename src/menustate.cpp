#include "menustate.h"
#include "state.h"
MenuState::MenuState(){

}

void MenuState::Draw(){

  io::printMsg("Continue", 32, 16, 15, Green);
  io::printMsg("Quit", 32, 18, 15, Green);
  io::flip();
}

void MenuState::Update(){
  // Handle menu navigation
  Keys key = io::Input();
  switch(key){
  case E_QUIT:
    Game::isRunning = false;
    states::pop();
    break;
  case K_q:
    Game::isRunning = false;
    states::pop();
    break;
  default:
    break;
  }
    
}
