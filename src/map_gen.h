#ifndef MAP_GEN_H
#define MAP_GEN_H

#include "globals.h"
#include "helper.h"
#include <vector>
#include <list>

class bsp{

 public:
  bsp* rightNode;
  bsp* leftNode;
  int x;
  int y;
  int w;
  int h;
  
  bsp(int x, int y, int w, int h);

  bool split();

  
};

namespace mapGen{
  
  void init();

  extern std::list<bsp*> nodes;
  extern char _map[g::MAP_WIDTH][g::MAP_HEIGHT];
  void init();

  void createConnection();
  void fillRect(const R &r, char c);
  void createRooms(bsp *n);
  void createHorizontalTunnel(P p1, P p2);
  void createVerticalTunnel(P p1, P p2);
  void addMonster(P p);
  void addDoors();
  void drawMap();
  std::string getMapStr();
  
  extern std::vector<R*> rooms;
  
}

#endif
