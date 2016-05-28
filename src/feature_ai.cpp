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

  Keys key = engine.Input();
  switch(key){
  case K_UP:
    dy = -1;
    break;
  case K_DOWN:
    dy = 1;
    break;
  case K_RIGHT:
    dx = 1;
    break;
  case K_LEFT:
    dx = -1;
    break;
  case E_QUIT:
    game.isRunning = false;
    break;
  case K_q:
    game.isRunning = false;
    break;
  case K_c:
    Map::closeDoor(a->pos);
    break;
  default:
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
  // check for door
  if(Map::cells[targetX][targetY]._glyph == '+'){
    Map::openDoor(P(targetX,targetY));
    return true;
  }
  
  // Check collision with walls
  if(!Map::cells[targetX][targetY].isBlocking && targetX < globals::MAP_WIDTH && targetY < globals::MAP_HEIGHT && targetX >= 0 && targetY >= 0){
    a->pos.set(P(targetX, targetY));
    return true;
  }
  return false;
}
