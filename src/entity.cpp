#include "entity.h"
#include "sdl_wrapper.h"
#include "f_actor.h"
#include "f_mortal.h"
#include "f_fighter.h"
#include "f_container.h"

Entity::Entity(P p, std::string name, char glyph, cColor c, std::string desc) :
  pos(p), _name(name), _glyph(glyph),
  _color(c), _description(desc) {
  act = nullptr;
  mortal = nullptr;
  fighter = nullptr;
  container = nullptr;
  item = nullptr;
  _spawnUpperLimit = -1; // -1 indicates that entity can spawn on any floor
  _spawnLowerLimit = -1;
  
  }

Entity::~Entity(){
  
  delete act;
  delete mortal;
  delete fighter;
  delete container;
}

void Entity::Render(){
  io::renderGlyph(_glyph, pos.x, pos.y, _color);
}

void Entity::Update(){
  if(act) act->Act(*this);
}
