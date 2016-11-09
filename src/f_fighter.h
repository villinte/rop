#ifndef F_FIGHTER_H
#define F_FIGHTER_H
#include <memory>

class Entity;
class Mortal;

class Fighter{
 public:
  int atkPower;
  Fighter(int atkP);
  ~Fighter() {}
  void Attack(Entity &a, Entity &target);
};

#endif
