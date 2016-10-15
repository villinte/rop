#include "f_fighter.h"
#include "entity.h"
#include "f_mortal.h"
#include "gui.h"
#include <string>

Fighter::Fighter(int atkP) : atkPower(atkP){
}

void Fighter::Attack(Entity &a, Entity &target){

  if(!target.mortal || target.mortal->isDead()){
    std::string tempMsg = "Could not attack " + target._name + ".";
    Gui::LogMsg(tempMsg);
  }
  else if(target.mortal && !target.mortal->isDead()){

    if( atkPower - (target.mortal->armor) > 0){
      int dmg = target.mortal->takeDmg(target, atkPower);
      if(!target.mortal->isDead()){
	std::string tempMsg = "Attacks " + target._name + " for " + std::to_string(dmg) + " damage.";
	Gui::LogMsg(tempMsg);
      }
    }else{
      std::string tempMsg = "Attacks " + target._name + ", attack missed.";
      Gui::LogMsg(tempMsg);
    }
    
    }
}
