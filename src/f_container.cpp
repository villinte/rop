#include "f_container.h"
#include "entity.h"
#include <algorithm>
#include "game.h"

bool Container::addItem(Entity &a){
  if(size > 0 && inv.size() >= size){
    return false;
  }
  inv.push_back(&a);
  std::sort(inv.begin(), inv.end());
  return true;
}

bool Container::pickUpItem(Entity &item_entity, Entity &using_entity){
  if ( using_entity.container && using_entity.container->addItem(item_entity) ) {
    for(unsigned i = 0; i < Game::actors.size(); ++i){
      if(Game::actors[i].get() == &item_entity){
	Game::actors.erase(Game::actors.begin()+i);
	break;
      }
    }
    return true;
  }
  return false;
}

bool Container::removeItem(Entity &a){
  //  inv.remove(&a);
    
  
  for(unsigned i = 0; i < inv.size(); ++i){
    if(inv[i] == &a){
      inv.erase(inv.begin()+i);
      std::sort(inv.begin(), inv.end());
      return true;
    }
  }
  
  return false;
}

Container::Container(unsigned size) : size(size){
  
}
