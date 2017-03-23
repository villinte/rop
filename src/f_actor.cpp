#include "f_actor.h"
#include "sdl_wrapper.h"
#include "entity.h"
#include "game.h"
#include "helper.h"
#include "map.h"
#include <cmath>
#include <iostream>
#include <memory>
#include "f_mortal.h"
#include "f_fighter.h"
#include "debug_print.h"
#include "pathfinding.h"

PlayerActor::PlayerActor(int speed) {
  this->speed = speed;
  this->energy = 10;
}

PlayerActor::~PlayerActor(){

}

void PlayerActor::Act(Entity &a) {

  bool Has_Acted = false;
  if(Game::p_dx != 0 || Game::p_dy != 0){
    if(Move(a, P(a.pos.x+Game::p_dx, a.pos.y+Game::p_dy))){
      Game::newTurn();
      Has_Acted = true;
    }
  }
  if(Has_Acted){
    Map::computeFov();
    energy -= g::TURN_COST;
  }
  // end of turn
}

bool PlayerActor::Move(Entity &a, P p){
  // check for door
  if(Map::cells[p.x][p.y]._glyph == '+'){
    Map::openDoor(p);
    return true;
  }
  
  //Check for actors to interact with
  for(auto & t : Game::actors){
    
    if(t.get()->pos == p && t.get()->mortal && !(t.get()->mortal->isDead())){
      a.fighter->Attack(a, *t);
      return true;
    }

    if(t->pos == p && t->_glyph == '<'){
      Debug::print("In stairs");
      Map::nextLevel();
      return true;
    }
    
  }
  
  // Check collision with walls
  if(!Map::cells[p.x][p.y]._block && p.x < g::MAP_WIDTH && p.y < g::MAP_HEIGHT && p.x >= 0 && p.y >= 0){
    a.pos.set(p);
    return true;
  }


  
  return false;
}

void PlayerActor::newTurn(){
  energy += speed;
}

bool PlayerActor::monsterInFov(){

  for(auto &t : Game::actors){

    if(t != Game::player && Map::cells[t->pos.x][t->pos.y].isSeen){
      if(t->mortal){
	if(t->mortal->isAlive == true)
	  return true;
      }
    }
    
  }
  return false;
}

MonsterActor::MonsterActor(int speed){
  this->energy = 0;
  this->speed = speed;
  this->aware = 0;
}

void MonsterActor::Act(Entity &a) {
  //if Dead
  if(a.mortal && a.mortal->isDead()){
    return;
    }  
  // If player is in field of view
  if(Map::cells[a.pos.x][a.pos.y].isSeen){
    aware = 5;
  }
  
  
  if(aware > 0){
    //is player next too monster?
    int dx = Game::player->pos.x - a.pos.x;
    int dy = Game::player->pos.y - a.pos.y;
    float distance=sqrtf(dx*dx+dy*dy);
    if ( distance >= 2 ) {      
      std::vector<P> moves = PF::findPath(a.pos, Game::player->pos, true);
      Move(a, moves.back());
      aware--;
    }
    else if ( a.fighter ) {
      a.fighter->Attack(a,*Game::player);
    }
    
  }
  else{ // wander
    Wander(a);
  }
  energy -= g::TURN_COST;
}

void MonsterActor::Wander(Entity &a){
  int dir = Rng::randInt(0,4);
  int dx = 0;
  int dy = 0;
  switch(dir){
  case 0://north
    dy = -1;
    break;
  case 1: //east
    dx = 1;
    break;
  case 2: //south
    dy = 1;
    break;
  case 3:// west
    dx = -1;
    break;
  }
  
  Move(a, P(a.pos.x+dx, a.pos.y+dy));    

}

void MonsterActor::Move(Entity &a, P p) {

  // Check collision with walls
  if(!Map::cells[p.x][p.y]._block && p.x < g::MAP_WIDTH && p.y < g::MAP_HEIGHT && p.x >= 0 && p.y >= 0){
    a.pos.set(p);
  }
  
}

void MonsterActor::newTurn(){
  energy += speed;
}

					

				       
