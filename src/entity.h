#ifndef ENTITY_H
#define ENTITY_H

#include "helper.h"
#include "globals.h"

#include <memory>

class sdlEngine;
class Mortal;
class Ai;

class Entity{
 public:
  Entity(P p, std::string name, char glyph, cColor c);
  ~Entity();

  void Render();
  void Update();
  
  //Components
  std::unique_ptr<Ai> ai;
  std::unique_ptr<Mortal> mortal;

  //std::unique_ptr<Fighter> fighter;

  P pos;
  std::string _name;
  char _glyph;
  cColor _color;
  bool _block;
  
 private:
  
};

#endif
