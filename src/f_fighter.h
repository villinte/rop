#ifndef F_FIGHTER_H
#define F_FIGHTER_H
#include <memory>

class Entity;
class Mortal;

class Fighter{
 public:
  Fighter(int atkR, int hitR);
  ~Fighter() {}
  void Attack(Entity &a, Entity &target);
  void modAtk(int mod){
    atkMod += mod;
  }
  void modHit(int mod){
    hitMod += mod;
  }
 private:
  int atkRating;
  int atkMod;
  int hitRating;
  int hitMod;

};

#endif
