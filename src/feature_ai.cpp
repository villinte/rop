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
	  dx = 1;
	  break;	
	case SDLK_LEFT:
	  dx = -1;
	  break;
	case SDLK_UP:
	  dy = -1;
	  break;
	case SDLK_DOWN:
	  dy = 1;
	  break;
	}
      break;
    }

  if(dx != 0 || dy != 0){
    if(Move(a, a->pos.x+dx, a->pos.y+dy)){
      Map::computeFov();
    }
  }
  
}

void PlayerAi::Update(Actor *a) {
  Input(a);
}

bool PlayerAi::Move(Actor *a, int targetX, int targetY){
  if(!Map::cells[targetX][targetY].isBlocking && targetX < globals::MAP_WIDTH && targetY < globals::MAP_HEIGHT && targetX >= 0 && targetY >= 0){
    a->pos.set(P(targetX, targetY));
    return true;
  }
  return false;
}
