#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"
#include "game.h"
#include "sdl_wrapper.h"
#include <memory.h>
#include "state.h"


const int _CONTINUE = 0;
const int _QUIT     = 1;

enum Active{
  CONTINUE,
  QUIT  
};

class MenuState : public State{

 public:
  MenuState();
  void Update();
  void Draw();
  bool draw_overlayed() const{
    return true;
  }

  int current;
  Active currentActive;
  
};

#endif
