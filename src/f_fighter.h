#ifndef F_FIGHTER_H
#define F_FIGHTER_H

class Entity;
class Mortal;

class Fighter{
 public:
  int atkPower;
  Fighter(int atkP);
  virtual ~Fighter() {}
  void Attack(Entity &a, Entity &target);
};

#endif
