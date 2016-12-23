#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"
#include <string>

class newPlayer : public State{
 public:
  newPlayer();
  void Update();
  void Draw();
  bool draw_overlayed() const{
    return false;
  }

  std::string nick;

  
};

namespace PlayerName{
  std::string inputName();
  
}

#endif
