#ifndef MAINMENU_H
#define MAINMENU_H

#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"
#include "game.h"
#include "sdl_wrapper.h"
#include <memory.h>
#include "state.h"

enum MENUITEMS{
  LOAD_GAME,
  CREATE_NEW,
  HELP,
  QUIT,
  LAST_ENUM
};

class MainMenu : public State{

 public:
  MainMenu();
  void Update();
  void Draw();
  bool draw_overlayed() const{
    return true;
  }

  MENUITEMS current;
    
};

#endif
