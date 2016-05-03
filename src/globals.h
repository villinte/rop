#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
namespace globals {
  const int TILE_W = 16;
  const int TILE_H = 24;
  const int FONT_W = 16;
  const int FONT_H = 24;
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 720;
  const int MAP_WIDTH = SCREEN_WIDTH/TILE_W;
  const int MAP_HEIGHT = SCREEN_WIDTH/TILE_H;
}

struct Pos{
  int x;
  int y;
};

struct cColor{
  short int r;
  short int g;
  short int b;
};

const cColor Blue = {0,0,255};
const cColor White = {255,255,255};
const cColor Black = {139,137,137};
const cColor Green = {0, 255, 0};
const cColor Red = {255,0,0};

#endif