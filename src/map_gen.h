#ifndef MAP_GEN_H
#define MAP_GEN_H
#include "globals.h"
#include "helper.h"
#include <string>

namespace mapGen{

  extern char _map[globals::MAP_WIDTH][globals::MAP_HEIGHT];
  void init();
  void fillRect(const R &r, char c);
  bool buildRoom(R &r, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
  void createHorizontalTunnel(P p1, P p2);
  void createVerticalTunnel(P p1, P p2);
  void createMonster(unsigned int a, P p);
  std::string getMapStr();
}

#endif
