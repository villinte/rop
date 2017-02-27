#include "sdl_wrapper.h"
#include <iostream>
namespace io{

  namespace{
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Texture* _font;
    SDL_Texture* _texture;
  }


  void Init(){
    SDL_Init(SDL_INIT_VIDEO);
    
    _window = SDL_CreateWindow("RoP",
			       SDL_WINDOWPOS_UNDEFINED,
			       SDL_WINDOWPOS_UNDEFINED,
			       g::SCREEN_WIDTH,
			       g::SCREEN_HEIGHT,
			       0);
    
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
   
    
    SDL_Surface* loadedSurface = IMG_Load("gfx/16x24.png");
    
    if(loadedSurface == NULL)
      std::cout << "Could not open " << "16x24.png" << std::endl;
    
    SDL_SetColorKey(loadedSurface,SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255 ) );
    
    _texture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    
    SDL_FreeSurface(loadedSurface);
    
    
    loadedSurface = IMG_Load("gfx/16x16.png");
    
    if(loadedSurface == NULL)
      std::cout << "Could not open " << "16x16.png" << std::endl;
    
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
    
    _font = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    
    SDL_FreeSurface(loadedSurface);
  
  } // Init

  void Cleanup(){
    SDL_DestroyTexture(_texture);
    SDL_DestroyTexture(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
  } // Cleanup
  
  void printMsg(std::string str, int x, int y, int w, cColor cC){
  
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
  } //printMsg

  void renderChar(char c, int x, int y, cColor cC){
    SDL_Rect srcRct;
    if(c >= ' ' && c <= '/'){
      srcRct.y = 0;
      srcRct.x = ((int)c-32)*g::FONT_W;
      srcRct.w = g::FONT_W;
      srcRct.h = g::FONT_H;
    }
    else if(c >= '0' && c <= '?'){
      srcRct.y = 1*g::FONT_H;
      srcRct.x = ((int)c-48)*g::FONT_W;
      srcRct.w = g::FONT_W;
      srcRct.h = g::FONT_H;

    }
    else if(c >= '@' && c <= 'O'){
      srcRct.y = 2*g::FONT_H;
      srcRct.x = ((int)c-64)*g::FONT_W;
      srcRct.w = g::FONT_W;
      srcRct.h = g::FONT_H;
    }
    else if(c >= 'P' && c <= '_'){
      srcRct.y = 3*g::FONT_H;
      srcRct.x = ((int)c-80)*g::FONT_W;
      srcRct.w = g::FONT_W;
      srcRct.h = g::FONT_H;
    }
    else if(c >= '\'' && c <= 'o'){
      srcRct.y = 4*g::FONT_H;
      srcRct.x = ((int)c-96)*g::FONT_W;
      srcRct.w = g::FONT_W;
      srcRct.h = g::FONT_H;
    }
    else if(c >= 'p' && c <= '~'){
      srcRct.y = 5*g::FONT_H;
      srcRct.x = ((int)c-112)*g::FONT_W;
      srcRct.w = g::FONT_W;
      srcRct.h = g::FONT_H;
    }
    SDL_Rect dstRct;
    dstRct.x = x*g::FONT_W;
    dstRct.y = y*g::FONT_H;
    dstRct.w = g::FONT_W;
    dstRct.h = g::FONT_H;
  
    SDL_Rect rect = {dstRct.x, dstRct.y, dstRct.w, dstRct.h};
    SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
    SDL_RenderFillRect(_renderer, &rect);
    SDL_RenderCopy(_renderer, _font, &srcRct, &dstRct);

  } // renderChar
  
  void renderGlyph(char c, int x, int y, cColor cC){
    SDL_Rect srcRct;
    if(c >= ' ' && c <= '/'){
      srcRct.y = 0;
      srcRct.x = ((int)c-32)*g::FONT_W;
      srcRct.w = g::GLYPH_W;
      srcRct.h = g::GLYPH_H;
    }
    else if(c >= '0' && c <= '?'){
      srcRct.y = 1*g::GLYPH_H;
      srcRct.x = ((int)c-48)*g::GLYPH_W;
      srcRct.w = g::GLYPH_W;
      srcRct.h = g::GLYPH_H;

    }
    else if(c >= '@' && c <= 'O'){
      srcRct.y = 2*g::GLYPH_H;
      srcRct.x = ((int)c-64)*g::GLYPH_W;
      srcRct.w = g::GLYPH_W;
      srcRct.h = g::GLYPH_H;
    }
    else if(c >= 'P' && c <= '_'){
      srcRct.y = 3*g::GLYPH_H;
      srcRct.x = ((int)c-80)*g::GLYPH_W;
      srcRct.w = g::GLYPH_W;
      srcRct.h = g::GLYPH_H;
    }
    else if(c >= '\'' && c <= 'o'){
      srcRct.y = 4*g::GLYPH_H;
      srcRct.x = ((int)c-96)*g::GLYPH_W;
      srcRct.w = g::GLYPH_W;
      srcRct.h = g::GLYPH_H;
    }
    else if(c >= 'p' && c <= '~'){
      srcRct.y = 5*g::GLYPH_H;
      srcRct.x = ((int)c-112)*g::GLYPH_W;
      srcRct.w = g::GLYPH_W;
      srcRct.h = g::GLYPH_H;
    }
    SDL_Rect dstRct;
    dstRct.x = x*g::GLYPH_W;
    dstRct.y = y*g::GLYPH_H;
    dstRct.w = g::GLYPH_W;
    dstRct.h = g::GLYPH_H;
  
    SDL_Rect rect = {dstRct.x, dstRct.y, dstRct.w, dstRct.h};
    SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
    SDL_RenderFillRect(_renderer, &rect);
    SDL_RenderCopy(_renderer, _texture, &srcRct, &dstRct);

  } // renderGlyph


  void DrawLine(P p1, P p2, cColor cC){
    SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 255);
    SDL_RenderDrawLine(_renderer, p1.x, p1.y, p2.x, p2.y);
  } // DrawLine

  void drawClearRect(P p, cColor cC){
    SDL_Rect rect = {p.x*g::GLYPH_W, p.y*g::GLYPH_H, g::GLYPH_W, g::GLYPH_H};
    SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 100);

    SDL_RenderDrawRect(_renderer, &rect);
  } // drawClearRect

  void drawSquare(SDL_Rect r, cColor cC){
    SDL_SetRenderDrawColor(_renderer, cC.r, cC.g, cC.b, 100);
    SDL_RenderFillRect(_renderer, &r);
  } // drawSquare

  Keys Input(){

    SDL_Event event;

    while(SDL_PollEvent(&event)){
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
	  case SDLK_KP_6:
	    return K_RIGHT;
	    break;
	  case SDLK_LEFT:
	    return K_LEFT;
	    break;
	  case SDLK_KP_4:
	    return K_LEFT;
	    break;
	  case SDLK_UP:
	    return K_UP;
	    break;
	  case SDLK_KP_8:
	    return K_UP;
	    break;
	  case SDLK_DOWN:
	    return K_DOWN;
	    break;
	  case SDLK_KP_2:
	    return K_DOWN;
	    break;
	  case SDLK_KP_1:
	    return K_KP_1;
	    break;
	  case SDLK_KP_3:
	    return K_KP_3;
	    break;
	  case SDLK_KP_5:
	    return K_KP_5;
	    break;
	  case SDLK_KP_9:
	    return K_KP_9;
	    break;
	  case SDLK_KP_7:
	    return K_KP_7;
	    break;
	  case SDLK_END:
	    return K_END;
	    break;
	  case SDLK_PAGEDOWN:
	    return K_PGDN;
	    break;
	  case SDLK_PAGEUP:
	    return K_PGUP;
	    break;
	  case SDLK_HOME:
	    return K_HOME;
	    break;
	  case SDLK_c:
	    return K_c;
	    break;
	  case SDLK_v:
	    return K_v;
	    break;
	  case SDLK_s:
	    return K_s;
	    break;
	  case SDLK_l:
	    return K_l;
	    break;
	  case SDLK_g:
	    return K_g;
	    break;
	  case SDLK_i:
	    return K_i;
	    break;
	  case SDLK_ESCAPE:
	    return K_ESC;
	    break;
	  case SDLK_RETURN:
	    return K_RETURN;
	    break;
	  }
	break;
      }

    }
    return K_UNKNOWN;
    
  } // Input

  
  void clear(){
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
  } // clear

  void flip(){
    SDL_RenderPresent(_renderer);
  } // flip
  
}
