#ifndef ENTITY_H
#define ENTITY_H

#include "helper.h"
#include "globals.h"
#include <memory>
#include "f_actor.h"
#include "f_item.h"

class Actor;
class Mortal;
class Fighter;
class Container;
class Item;

class Entity{
 public:
  Entity(P p, std::string name, char glyph, cColor c, std::string des);
  ~Entity();
  
  void Render();
  void Update();

  bool operator == (const Entity& str) const{
    return (_name == str._name);
  }
  bool operator < (const Entity& str) const{
    return (_name < str._name);
  }

  P getP() {return pos;}
  
  //Components
  Actor *act;
  Mortal *mortal;
  Fighter *fighter;
  Container *container;
  Item *item;
  
  P pos;
  std::string _name;
  char _glyph;
  cColor _color;
  bool _block;
  bool _visible;
  int _spawnUpperLimit;
  int _spawnLowerLimit;
  std::string _description;
  
 private:
  
};

#endif
