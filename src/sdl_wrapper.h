#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "globals.h"
#include "helper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace io{
  
  void Init();
  void Cleanup();

  void printMsg(std::string str, int x, int y, int w, cColor cC);
  void renderChar(char c, int x, int y, cColor cC);
  void renderGlyph(char c, int x, int y, cColor cC);
  void DrawLine(P p1, P p2, cColor cC);
  void drawClearRect(P p, cColor cC);
  void drawSquare(SDL_Rect r, cColor cC);
  Keys Input();
  void clear();  

  void flip();
  
} // namespace io

#endif
