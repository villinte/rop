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
  virtual void newTurn() = 0;
  int energy;
  int speed;
 protected:
};

class MonsterAi : public Ai {
 public:
  MonsterAi(int speed);
  
  void Act(Entity *a);
  void newTurn();
 protected:
  void Wander(Entity *a);
  void Move(Entity *a, P p);
};

class PlayerAi : public Ai{
 public:
  int Level;
  PlayerAi(int speed);
  ~PlayerAi();
  
  void newTurn();
  void Act(Entity *a);
 protected:
  void Input(Entity *a);
  bool Move(Entity *a, P p);
 
};




#endif
