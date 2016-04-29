#include "game.h"


Game::Game(){
  x = 9;
  y = 6;
  isRunning = true;
  
}

Game::~Game(){

}

void Game::Render(){
  engine.clear();
  
  map.Render();
  engine.renderChar('@',x,y,Red);
  engine.printMsg("hejhej", 10, 30, 50);
  engine.flip();
}

void Game::Update(){
  // Handle Inputs
  SDL_Event event;
  SDL_WaitEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
	{
	case SDLK_q:
	  isRunning = false;
	  break;
	case SDLK_RIGHT:
	  x += 16;
	  break;
	case SDLK_LEFT:
	  x -= 16;
	  break;
	case SDLK_UP:
	  y -= 16;
	  break;
	case SDLK_DOWN:
	  y += 16;
	  break;
	}
      break;
    }
  
}
