#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
namespace globals {
  const int TILE_W = 16;
  const int TILE_H = 24;
  const int FONT_W = 16;
  const int FONT_H = 16;
  const int GLYPH_W = 16;
  const int GLYPH_H = 24;
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 720;
  const int MAP_WIDTH = 80;
  const int MAP_HEIGHT = 22;
  const int SCREEN_WIDTH_TILE = SCREEN_WIDTH/TILE_W;
  const int SCREEN_HEIGHT_TILE = SCREEN_WIDTH/TILE_H;
  const int TURN_COST = 10;
  const int MAX_STR_LEN = 100;
}

struct cColor{
  short int r;
  short int g;
  short int b;
};

// K - keys,  E - events
enum Keys{
  K_UP, K_DOWN, K_LEFT, K_RIGHT,
  K_a,K_b,K_c,K_d,K_e,K_f,K_g,K_h,K_i,K_j,K_k,K_l,K_m,K_n,K_o,K_p,K_q,
  K_r,K_s,K_t,K_u,K_v,K_w,K_x,K_y,K_z,
  K_A,K_B,K_C,K_D,K_E,K_F,K_G,K_H,K_I,K_J,K_K,K_L,K_M,K_N,K_O,K_P,K_Q,
  K_R,K_S,K_T,K_U,K_V,K_W,K_X,K_Y,K_Z,
  K_ESC,
  K_RETURN,
  E_QUIT,
  K_UNKNOWN
};

enum _DIR{
  NORTH,
  NORTHEAST,
  EAST,
  SOUTHEAST,
  SOUTH,
  SOUTHWEST,
  WEST,
  NORTHWEST,
  UNKNOWN  
};

const cColor Blue  = {0,0,255};
const cColor White = {255,255,255};
const cColor Black = {0,0,0};
const cColor Green = {0, 255, 0};
const cColor Red   = {255,0,0};
const cColor Brown = {139,69,19};
const cColor Pink  = {255,105,180};
const cColor BloodRed = {138,7,7};
const cColor Orange = {255,140,0};
const cColor Grey   = {139,137,137};

#endif
