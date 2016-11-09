#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"
#include "game.h"
#include "sdl_wrapper.h"
#include <memory.h>
#include "state.h"

class MenuState : public State{

 public:
  MenuState();
  void Update();
  void Draw();
  bool draw_overlayed() const{
    return true;
  }
  
  
};

#endif
