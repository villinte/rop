#ifndef F_ACTOR_H
#define F_ACTOR_H

#include <memory>

class Entity;
class Mortal;
class Fighter;
class P;


class Actor{
 public:
  virtual void Act(Entity &a) = 0;
  virtual ~Actor() {}
  virtual void newTurn() = 0;
  virtual bool monsterInFov() = 0;
  int energy;
  int speed;
 protected:
};

class MonsterActor : public Actor {
 public:
  MonsterActor(int speed);
  
  void Act(Entity &a);
  void newTurn();
  bool monsterInFov(){ return false;}
 protected:
  void Wander(Entity &a);
  void Move(Entity &a, P p);
};

class PlayerActor : public Actor{
 public:
  int Level;
  PlayerActor(int speed);
  ~PlayerActor();

  bool monsterInFov();
  
  void newTurn();
  void Act(Entity &a);
 protected:
  void Input(Entity &a);
  bool Move(Entity &a, P p);
 
};

#endif
