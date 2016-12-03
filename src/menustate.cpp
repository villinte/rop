#include "menustate.h"
#include "state.h"

MenuState::MenuState(){
  current = _CONTINUE;
}

void MenuState::Draw(){
  currentActive = (Active)current;
  if(currentActive == CONTINUE){
    io::printMsg("Continue", 32, 16, 15, Green);
  }
  else{
    io::printMsg("Continue", 32, 16, 15, Grey);
  }
  if(currentActive == QUIT){
    io::printMsg("Quit", 32, 18, 15, Green);
  }
  else{
    io::printMsg("Quit", 32, 18, 15, Grey);
  }
  
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

  case K_UP:
    if(current == _CONTINUE){
      current = _QUIT;
    }
    else{
      current--;
    }
    break;

  case K_DOWN:
    if(current < _QUIT){
      current++;
    }
    else{
      current = _CONTINUE;
    }
    break;
    
  case K_RETURN:
    if(current == CONTINUE)
      states::pop();
    else if(current == QUIT){
      Game::isRunning = false;
      states::pop();
    }
    break;
  default:
    break;
  }
    
}
