#ifndef F_ITEM_H
#define F_ITEM_H

#include <string>
#include <memory>

class Entity;
class Container;
class Mortal;

class Item{
 public:
  virtual bool Use(std::unique_ptr<Entity> &item_actor, std::unique_ptr<Entity> &using_actor);
  virtual ~Item() {}
  virtual std::string getMsg() = 0;
};

class Healing : public Item{
 public:
  bool Use(std::unique_ptr<Entity> &item_actor, std::unique_ptr<Entity> &using_actor);
  Healing(int amount, std::string _use_msg);
  std::string getMsg(){ return _use_msg; } 
 private:
  int amount;
  std::string _use_msg;
};


#endif
