#ifndef F_ITEM_H
#define F_ITEM_H

class Entity;
class Container;
class Mortal;

class Item{
 public:
  virtual bool Use(Entity &item_actor, Entity &using_actor);
  virtual ~Item() {}
  
};

class Healing : public Item{
 public:
  bool Use(Entity &item_actor, Entity &using_actor);
  Healing(int amount);

 private:
  int amount;
};


#endif
