#include "game.h"
#include "sdl_wrapper.h"
#include "mainmenu.h"

#include "data_load.h"

class GameState;

int main(){

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
