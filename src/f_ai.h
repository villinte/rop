/*
  Feature_AI -- Component that handles entity's acting, fightning, movement etc.
 */
#ifndef F_AI_H
#define F_AI_H

class Entity;
class Mortal;

class P;


class Ai{
 public:
  virtual void Act(Entity *a) = 0;
  virtual ~Ai() {}
 protected:
};

class MonsterAi : public Ai {
 public:
  MonsterAi();
  void Act(Entity *a);
 protected:
  void Wander(Entity *a);
  void Move(Entity *a, P p);
};

class PlayerAi : public Ai{
 public:
  int Level;
  PlayerAi();
  ~PlayerAi();

  void Act(Entity *a);
 protected:
  void Input(Entity *a);
  bool Move(Entity *a, P p);
 
};




#endif
