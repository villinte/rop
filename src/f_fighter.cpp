#include "f_fighter.h"
#include "entity.h"
#include "f_mortal.h"
#include <string>
#include "gui.h"
#include <iostream>
#include "helper.h"
#include "game.h"

Fighter::Fighter(int atkR, int hitR) : atkRating(atkR), hitRating(hitR){
  hitMod = 0;
  atkMod = 0;
}

void Fighter::Attack(Entity &a, Entity &target){

  if(!target.mortal || target.mortal->isDead()){
    std::string tempMsg = "Could not attack " + target._name + ".";
    Gui::LogMsg(tempMsg);
  }
  else if(target.mortal && !target.mortal->isDead()){

    // throw d20 for hit and for dodge --  16+ = critical hit which adds 50% dmg.
    unsigned int hit = Rng::randInt(1,20) + a.fighter->hitRating;
    unsigned int dodge = Rng::randInt(1,20) + target.mortal->dodgeRating;
    std::string t_name = target._name;
    std::string a_name = a._name;
    
    if(hit > dodge){
      // Successfull attack - Normal
      if( atkRating - (target.mortal->armor) > 0){
	int dmg = target.mortal->takeDmg(target, atkRating);
	if(!target.mortal->isDead()){
	  std::string tempMsg = " ";
	  if(a_name == Game::player->_name){
	    tempMsg = "You hit " +
	      t_name + " for " + std::to_string(dmg) + " damage.";
	  }
	  else{
	    tempMsg = a_name + " hits you for " + std::to_string(dmg) + " damage.";
	  }
	  Gui::LogMsg(tempMsg);
	}
	else{
	  std::string tempMsg = " ";
	  if(a_name == Game::player->_name){
	    tempMsg = "You hit " + t_name + " for " + std::to_string(dmg)
	      + " damage.";
	  }
	  else{
	    tempMsg = a_name + " hits you for " + std::to_string(dmg) + " damage.";
	  }
	  Gui::LogMsgBeforeLast(tempMsg);
	}
      }
    }
    else if(hit > (dodge + 5)){
      // Successfull attack - Critical
      if( atkRating+(atkRating/2) - (target.mortal->armor) > 0){
	int dmg = target.mortal->takeDmg(target, atkRating);
	if(!target.mortal->isDead()){
	  std::string tempMsg = " ";
	  if(a_name == Game::player->_name){
	    tempMsg = "You hit " + t_name + " for " + std::to_string(dmg) + " critical damage.";
	  }
	  else{
	    tempMsg = a_name + " hits you for " + std::to_string(dmg) + " critical damage.";
	  }
	  Gui::LogMsg(tempMsg);
	}
	else{
	  std::string tempMsg = " ";
	  if(a_name == Game::player->_name){
	    tempMsg = "You hit " + t_name + " for " + std::to_string(dmg)
	      + " damage.";
	  }
	  else{
	    tempMsg = a_name + " hits you for " + std::to_string(dmg) + " damage.";
	  }
	  Gui::LogMsgBeforeLast(tempMsg);
	}
      }
    }
    else if(hit < dodge){ // miss
      std::string tempMsg = " ";
      if(a_name == Game::player->_name){
	tempMsg = "You try to hit " + t_name + ", attack missed.";
      }
      else{
	tempMsg = a_name + " tries to hit you, attack missed.";
      }
      Gui::LogMsg(tempMsg);
    }
    
  }
}
