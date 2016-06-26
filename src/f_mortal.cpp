#include "f_mortal.h"
#include "entity.h"
#include "game.h"
#include "gui.h"
#include "f_ai.h"

Mortal::Mortal(int maxHp, int armor, std::string corpseName, int xp) :
  maxHp(maxHp), armor(armor), corpseName(corpseName), xp(xp) {
  hp = maxHp;
}

int Mortal::takeDmg(Entity *a, int dmg){
  dmg -= armor;
  if(dmg > 0){
    hp -= dmg;
    if(hp <= 0){
      die(a);
    }
  }
  else{
    dmg = 0;
  }
  return dmg;
}

int Mortal::Heal(int amount){
  hp += amount;
  if(hp > maxHp){
    amount -= hp-maxHp;
    hp = maxHp;
  }
  return amount;
}

void Mortal::die(Entity *a){
  a->_glyph = '%';
  a->_color = BloodRed;
  a->_name = corpseName;
  a->_block = false;
  a->ai->energy = 0;
  
}

MonsterMortal::MonsterMortal(int maxHp, int armor, std::string corpseName, int xp) :
  Mortal(maxHp,armor,corpseName,xp) {
  
}

void MonsterMortal::die(Entity *a) {
  // Send msg to log
  std::string tempMsg = a->_name + " has died.";
  Gui::LogMsg(tempMsg);
  Game::player->mortal->xp += xp;
  Mortal::die(a);
}

PlayerMortal::PlayerMortal(int maxHp, int armor, std::string corpseName) :
  Mortal(maxHp,armor,corpseName,0) {
}

void PlayerMortal::die(Entity *a) {
  // send msg to log
  Gui::LogMsg("You died.");
  Mortal::die(a);
  // kill game.
}
