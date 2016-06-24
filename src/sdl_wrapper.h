#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H
#include <string>
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "helper.h"


class sdlEngine{
 public:
  sdlEngine();
  ~sdlEngine();

  void printMsg(std::string str, int x, int y, int w, cColor cC);
  void renderChar(char c, int x, int y, cColor cC);
  void renderGlyph(char c, int x, int y, cColor cC);
  void DrawLine(P p1, P p2, cColor cC);
  Keys Input();
  void clear(){
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->_renderer);
  }
  void flip(){ SDL_RenderPresent(this->_renderer); }
  
 private:
  SDL_Window* _window;
  SDL_Renderer* _renderer;
  SDL_Texture* _font;
  SDL_Texture* _texture;
  
};
extern sdlEngine engine;
#endif
