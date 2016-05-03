#include "game.h"
#include "sdl_wrapper.h"
sdlEngine engine;
Game game;

int main(int argc, char* argv[]){
  
  while(game.isRunning){
    game.Render();
    game.Update();    
  }  
  
  return 0;
}
