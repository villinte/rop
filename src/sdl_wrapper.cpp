#include "sdl_wrapper.h"
#include <iostream>

sdlEngine::sdlEngine(){
  SDL_Init(SDL_INIT_VIDEO);
  _window = SDL_CreateWindow("RoP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0);
  _renderer = SDL_CreateRenderer(_window, -1, 0);
  SDL_Surface* loadedSurface = IMG_Load("gfx/16x24.png");
  if(loadedSurface == NULL)
    std::cout << "Could not open " << "16x24.png" << std::endl;

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255 ) );
  _texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);

  loadedSurface = IMG_Load("gfx/16x16.png");
  if(loadedSurface == NULL)
    std::cout << "Could not open " << "16x16.png" << std::endl;

  SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
  _font = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
  SDL_FreeSurface(loadedSurface);
  
  
}

sdlEngine::~sdlEngine(){
  SDL_DestroyTexture(_texture);
  SDL_DestroyTexture(_font);
  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}


void sdlEngine::printMsg(std::string str, int x, int y, int w, cColor cC){
  int tX = x, tY = y;
  int cnt = 0;
  int maxW = w-x;
  for(unsigned int i = 0; i < str.length(); ++i){
    renderChar(str.at(i), tX, tY, cC);
    tX++;
    cnt++;
    if(cnt == maxW){
      tX = x;
      tY++;
    }
  }
}

void sdlEngine::renderGlyph(char c, int x, int y, cColor cC){
  SDL_Rect srcRct;
  if(c >= ' ' && c <= '/'){
    srcRct.y = 0;
    srcRct.x = ((int)c-32)*globals::FONT_W;
    srcRct.w = globals::GLYPH_W;
    srcRct.h = globals::GLYPH_H;
  }
  else if(c >= '0' && c <= '?'){
    srcRct.y = 1*globals::GLYPH_H;
    srcRct.x = ((int)c-48)*globals::GLYPH_W;
    srcRct.w = globals::GLYPH_W;
    srcRct.h = globals::GLYPH_H;

  }
  else if(c >= '@' && c <= 'O'){
    srcRct.y = 2*globals::GLYPH_H;
    srcRct.x = ((int)c-64)*globals::GLYPH_W;
    srcRct.w = globals::GLYPH_W;
    srcRct.h = globals::GLYPH_H;
  }
  else if(c >= 'P' && c <= '_'){
    srcRct.y = 3*globals::GLYPH_H;
    srcRct.x = ((int)c-80)*globals::GLYPH_W;
    srcRct.w = globals::GLYPH_W;
    srcRct.h = globals::GLYPH_H;
  }
  else if(c >= '\'' && c <= 'o'){
    srcRct.y = 4*globals::GLYPH_H;
    srcRct.x = ((int)c-96)*globals::GLYPH_W;
    srcRct.w = globals::GLYPH_W;
    srcRct.h = globals::GLYPH_H;
  }
  else if(c >= 'p' && c <= '~'){
    srcRct.y = 5*globals::GLYPH_H;
    srcRct.x = ((int)c-112)*globals::GLYPH_W;
    srcRct.w = globals::GLYPH_W;
    srcRct.h = globals::GLYPH_H;
  }
  SDL_Rect dstRct;
  dstRct.x = x*globals::GLYPH_W;
  dstRct.y = y*globals::GLYPH_H;
  dstRct.w = globals::GLYPH_W;
  dstRct.h = globals::GLYPH_H;
  
  SDL_Rect rect = {dstRct.x, dstRct.y, dstRct.w, dstRct.h};
  SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
  SDL_RenderFillRect(_renderer, &rect);
  SDL_RenderCopy(_renderer, _texture, &srcRct, &dstRct);

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
  dstRct.x = x*globals::FONT_W;
  dstRct.y = y*globals::FONT_H;
  dstRct.w = globals::FONT_W;
  dstRct.h = globals::FONT_H;
  
  SDL_Rect rect = {dstRct.x, dstRct.y, dstRct.w, dstRct.h};
  SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
  SDL_RenderFillRect(_renderer, &rect);
  SDL_RenderCopy(_renderer, _font, &srcRct, &dstRct);

}

void sdlEngine::DrawLine(P p1, P p2, cColor cC){
  SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
  SDL_RenderDrawLine(_renderer, p1.x, p1.y, p2.x, p2.y);
}

Keys sdlEngine::Input(){

  SDL_Event event;
  SDL_WaitEvent(&event);
  switch(event.type)
    {
    case SDL_QUIT:
      return E_QUIT;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
	{
	case SDLK_q:
	  return K_q;
	  break;
	case SDLK_RIGHT:
	  return K_RIGHT;
	  break;	
	case SDLK_LEFT:
	  return K_LEFT;
	  break;
	case SDLK_UP:
	  return K_UP;
	  break;
	case SDLK_DOWN:
	  return K_DOWN;
	  break;
	case SDLK_c:
	  return K_c;
	  break;
	}
      break;
    }

  return K_UNKNOWN;
}
