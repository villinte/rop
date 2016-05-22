#ifndef MAP_H
#define MAP_H
#include "globals.h"
#include "helper.h"

struct Cell{
  Cell();
  ~Cell();
  void Reset();
  
  P pos;
  char _glyph;
  cColor _color;
  
  bool isBlocking;

  bool isExplored;
  bool isSeen;
  int playerLos;
};
namespace Map{
  extern Cell cells[globals::MAP_WIDTH][globals::MAP_HEIGHT];
  
  void createMap();
  void cleanMap();
  void clearVision();
  void computeFov();
  void doFov(float x, float y);
  void renderMap();
  
  int spawnMonsters();
  
} //namespace Map

#endif
