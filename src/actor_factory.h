#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H
#include <memory>
#include "helper.h"
#include "globals.h"

class Entity;

namespace actor_factory{
  
  std::unique_ptr<Entity> make(const char* type, const P &p);
  
}


#endif
