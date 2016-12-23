#include "actor_factory.h"
#include "entity.h"
#include "f_mortal.h"
#include "f_fighter.h"
#include "f_actor.h"
#include "data_load.h"

namespace actor_factory{
  namespace{
    // Badly placed, move
    const cColor getColor(std::string s){
      if(s == "Blue")
	return Blue;
      else if(s == "White")
	return White;
      else if(s == "Black")
	return Black;
      else if(s == "Green")
	return Green;
      else if(s == "Red")
	return Red;
      else if(s == "Brown")
	return Brown;
      else if(s == "Pink")
	return Pink;
      else if(s == "BloodRed")
	return BloodRed;
      else if(s == "Orange")
	return Orange;
      else if(s == "Grey")
	return Grey;
      else
	return Red;
    }
  }  
  std::unique_ptr<Entity> make(const char* mon_type, const P &p){

    std::string description = dataLoad::getAttribute(mon_type, "info", "description");
    if(description == "UnknownAttribute")
      return nullptr;

    std::string glyph = dataLoad::getAttribute(mon_type, "look", "glyph");
    if(glyph == "UnknownAttribute")
      return nullptr;


    std::string color = dataLoad::getAttribute(mon_type, "look", "color");
    if(color == "UnknownAttribute")
      return nullptr;
    
    std::unique_ptr<Entity> e(new Entity(p, mon_type, glyph[0], getColor(color)));

    // If mortal
    std::string s_mortal = dataLoad::getAttribute(mon_type, "flags", "mortal");

    if(s_mortal == "1"){
      std::string s_hp = dataLoad::getAttribute(mon_type, "health", "max");
      if(s_hp == "UnknownAttribute")
	return nullptr;

      std::string s_corpse = dataLoad::getAttribute(mon_type, "look", "corpse");
      if(s_corpse == "UnknownAttribute")
	return nullptr;

      std::string s_xp = dataLoad::getAttribute(mon_type, "info", "experience");
      if(s_xp == "UnknownAttribute")
	return nullptr;
      
      Mortal* mMortal(new MonsterMortal(std::stoi(s_hp), 0, s_corpse, std::stoi(s_xp)));
      e->mortal = mMortal;
    }

    // If attacker
    std::string s_fighter = dataLoad::getAttribute(mon_type, "flags", "fighter");
    if(s_fighter == "1"){
      std::string s_power = dataLoad::getAttribute(mon_type, "attack", "power");
      if(s_power == "UnknownAttribute")
	return nullptr;

      Fighter* mFighter(new Fighter(std::stoi(s_power)));
      e->fighter = mFighter;
    }

     // If actor
    std::string s_actor = dataLoad::getAttribute(mon_type, "flags", "actor");
    if(s_actor == "1"){
      std::string s_energy = dataLoad::getAttribute(mon_type, "info", "energy");
      if(s_energy == "UnknownAttribute")
	return nullptr;

      Actor* mActor(new MonsterActor(std::stoi(s_energy)));
      e->act = mActor;
    }

    // Later add ability to carry a container of items    
    

    return std::move(e);    
    
  }

 
						 
}
