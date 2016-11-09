#ifndef F_CONTAINER_H
#define F_CONTAINER_H

#include <vector>
#include <memory>

class Entity;

class Container{

 public:
  bool removeItem(Entity &a);
  bool pickUpItem(Entity &item_entity, Entity &using_entity);
  bool addItem(Entity &a);
  Container(unsigned size);
  ~Container() {}

  //  std::vector<std::unique_ptr<Entity>> inv;
  std::vector<Entity*> inv;
  unsigned size;

 private:

  
};

#endif
