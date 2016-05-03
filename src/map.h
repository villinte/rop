#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>
#include "object.h"
class Map{

 public:
  Map();
  ~Map();

  void Render();
  void genMap();
  
 private:
  std::string mapStr;
  std::vector<OBJ_TYPE> tileVector;
  std::vector<int> mapVector;
  
};
#endif