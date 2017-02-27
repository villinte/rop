#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "state.h"
#include <string>

class instrState : public State{
 public:
  instrState(){};
  void Update();
  void Draw();
  bool draw_overlayed() const{
    return false;
  }

  
};

namespace Instructions{

  void Display();
  
}

#endif
