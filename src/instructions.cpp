#include "instructions.h"
#include "sdl_wrapper.h"

void instrState::Update(){
  Keys key = io::Input();
  switch(key){
  case K_ESC:
    states::pop();
    break;
    
    
  case K_RETURN:
    states::pop();
    break;
  default:
    break;
  }
}

void instrState::Draw(){
  io::printMsg("Movement: ", 7, 7, 100, White);
  io::printMsg("7 8 9", 8, 9, 100, White);
  io::printMsg("\\ /", 9, 10, 100, White);
  io::printMsg("4 5 6", 8, 11, 100, White);
  io::printMsg("/ \\", 9, 12, 100, White);
  io::printMsg("1 2 3", 8, 13, 100, White);

  io::printMsg("5: Rest for 5 turns", 8, 15, 100, White);
  io::printMsg("g: Grab item", 8, 16, 100, White);
  io::printMsg("i: Display Inventory", 8, 17, 100, White);
  io::printMsg("l: Display Message Log", 8, 18, 100, White);
  
  
}

namespace Instructions{

  void Display(){
   
    
  }
  
}
