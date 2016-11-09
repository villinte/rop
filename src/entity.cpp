#include "entity.h"
#include "sdl_wrapper.h"
#include "f_actor.h"
#include "f_mortal.h"
#include "f_fighter.h"
#include "f_container.h"

Entity::Entity(P p, std::string name, char glyph, cColor c) :
  pos(p), _name(name), _glyph(glyph),
  _color(c) {
  act = nullptr;
  mortal = nullptr;
  fighter = nullptr;
  container = nullptr;
  item = nullptr;
  
  }

Entity::~Entity(){
  if(act)
    delete act;
  
  if(mortal)
    delete mortal;
  
  if(fighter)
    delete fighter;
  
  if(container)
    delete container;
  
}

void Entity::Render(){
  io::renderGlyph(_glyph, pos.x, pos.y, _color);
}

void Entity::Update(){
  if(act) act->Act(*this);
}
