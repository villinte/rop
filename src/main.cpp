#include "game.h"
#include "sdl_wrapper.h"

class GameState;

int main(){

  io::Init();
  
  std::unique_ptr<State> playState(new GameState());

  states::push(std::move(playState));

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
