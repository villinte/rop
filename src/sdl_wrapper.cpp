#include "sdl_wrapper.h"
#include <iostream>

sdlEngine::sdlEngine(){
  SDL_Init(SDL_INIT_VIDEO);
  _window = SDL_CreateWindow("RoP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0);
  _renderer = SDL_CreateRenderer(_window, -1, 0);
  SDL_Surface* loadedSurface = IMG_Load("gfx/16x24.png");
  if(loadedSurface == NULL)
    std::cout << "Could not open " << "font.png" << std::endl;

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255 ) );
  _texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
  
}

sdlEngine::~sdlEngine(){
  SDL_DestroyTexture(_texture);
  SDL_FreeSurface(_font);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

void sdlEngine::printMsg(std::string str, int x, int y, int w){
  int yD = y;
  int xD = x;
  int cnt = 0;
  for(unsigned int i = 0; i < str.length(); ++i){
    renderChar(str.at(i), xD, yD,White);
    xD = xD + 16;
    ++cnt;
    if(cnt == w){
      xD = x;
      yD = yD + 24;
      cnt = 0;
    }
  }
}

void sdlEngine::renderChar(char c, int x, int y, cColor cC){
  SDL_Rect srcRct;
  if(c >= ' ' && c <= '/'){
    srcRct.y = 0;
    srcRct.x = ((int)c-32)*globals::FONT_W;
    srcRct.w = globals::FONT_W;
    srcRct.h = globals::FONT_H;
  }
  else if(c >= '0' && c <= '?'){
    srcRct.y = 1*globals::FONT_H;
    srcRct.x = ((int)c-48)*globals::FONT_W;
    srcRct.w = globals::FONT_W;
    srcRct.h = globals::FONT_H;

  }
  else if(c >= '@' && c <= 'O'){
    srcRct.y = 2*globals::FONT_H;
    srcRct.x = ((int)c-64)*globals::FONT_W;
    srcRct.w = globals::FONT_W;
    srcRct.h = globals::FONT_H;
  }
  else if(c >= 'P' && c <= '_'){
    srcRct.y = 3*globals::FONT_H;
    srcRct.x = ((int)c-80)*globals::FONT_W;
    srcRct.w = globals::FONT_W;
    srcRct.h = globals::FONT_H;
  }
  else if(c >= '\'' && c <= 'o'){
    srcRct.y = 4*globals::FONT_H;
    srcRct.x = ((int)c-96)*globals::FONT_W;
    srcRct.w = globals::FONT_W;
    srcRct.h = globals::FONT_H;
  }
  else if(c >= 'p' && c <= '~'){
    srcRct.y = 5*globals::FONT_H;
    srcRct.x = ((int)c-112)*globals::FONT_W;
    srcRct.w = globals::FONT_W;
    srcRct.h = globals::FONT_H;
  }
  SDL_Rect dstRct;
  dstRct.x = x;
  dstRct.y = y;
  dstRct.w = globals::FONT_W;
  dstRct.h = globals::FONT_H;
  
  SDL_Rect rect = {dstRct.x, dstRct.y, dstRct.w, dstRct.h};
  SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
  SDL_RenderFillRect(_renderer, &rect);
  SDL_RenderCopy(_renderer, _texture, &srcRct, &dstRct);

}
