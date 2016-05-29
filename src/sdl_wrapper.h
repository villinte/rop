#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H
#include <string>
#include "globals.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "helper.h"

// K - keys,  E - events
enum Keys{
  K_UP, K_DOWN, K_LEFT, K_RIGHT,
  K_a,K_b,K_c,K_d,K_e,K_f,K_g,K_h,K_i,K_j,K_k,K_l,K_m,K_n,K_o,K_p,K_q,
  K_r,K_s,K_t,K_u,K_v,K_w,K_x,K_y,K_z,
  K_A,K_B,K_C,K_D,K_E,K_F,K_G,K_H,K_I,K_J,K_K,K_L,K_M,K_N,K_O,K_P,K_Q,
  K_R,K_S,K_T,K_U,K_V,K_W,K_X,K_Y,K_Z,
  E_QUIT,
  K_UNKNOWN
};

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
