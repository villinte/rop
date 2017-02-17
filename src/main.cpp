#include "game.h"
#include "sdl_wrapper.h"
#include "mainmenu.h"
#include "debug_print.h"
#include "data_load.h"
#include <iostream>
class GameState;

int main(int argc, char *argv[]){

  if(argc >= 2){
    std::string debugFlag = argv[1];
    if(debugFlag == "-d"){
      Debug::Init(true);
    }
    else{
      Debug::Init(false);
    }
  }
  
  dataLoad::Init();
  
  io::Init();
  
  std::unique_ptr<State> mainMenuState(new MainMenu());
  states::push(std::move(mainMenuState));
  
  while(!states::is_empty()){
    
    states::start();

    if(states::is_empty()){
      break;
    }

    states::draw();
    
    states::update();
    
  } //while

  io::Cleanup();
  
}
