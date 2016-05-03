#include "feature_ai.h"
#include "sdl_wrapper.h"
#include "actor.h"
#include "game.h"

PlayerAi::PlayerAi(){

}

PlayerAi::~PlayerAi(){

}

void PlayerAi::Input(Actor *a){
  int dx = 0;
  int dy = 0;
  // Handle Inputs
  SDL_Event event;
  SDL_WaitEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      game.isRunning = false;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
	{
	case SDLK_q:
	  game.isRunning = false;
	  break;
	case SDLK_RIGHT:
	  dx = 16;
	  break;	
	case SDLK_LEFT:
	  dx = -16;
	  break;
	case SDLK_UP:
	  dy = -24;
	  break;
	case SDLK_DOWN:
	  dy = 24;
	  break;
	}
      break;
    }

  if(dx != 0 || dy != 0){
    Move(a, a->getX()+dx, a->getY()+dy);
  }
  
}

void PlayerAi::Update(Actor *a) {
  Input(a);
}

bool PlayerAi::Move(Actor *a, int targetX, int targetY){
  a->setX(targetX);
  a->setY(targetY);
  return true;
}
