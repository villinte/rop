#ifndef OBJECT_H
#define OBJECT_H
#include "globals.h"

struct OBJ_TYPE{
  int id;
  std::string nName;
  char nCharacter;
  cColor color;
  bool nPassable;  
};

#endif
