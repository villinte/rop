#include "entity.h"
#include "game.h"
#include "sdl_wrapper.h"
#include "f_mortal.h"
#include "f_ai.h"

Entity::Entity(P p, std::string name, char glyph, cColor c) :
  /* ai(nullptr),*/ mortal(nullptr),/* fighter(NULL),*/ pos(p), _name(name), _glyph(glyph),
  _color(c) {
  
}

Entity::~Entity(){
  
}

void Entity::Render(){
  Game::sdl.renderGlyph(_glyph, pos.x, pos.y, _color);
}

void Entity::Update(){
  if(ai) ai->Act(this);
}
