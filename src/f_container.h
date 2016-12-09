#ifndef F_CONTAINER_H
#define F_CONTAINER_H

#include <vector>
#include <memory>

class Entity;


class Container{

 public:

  bool removeItem(std::unique_ptr<Entity> &a);
  bool pickUpItem(std::unique_ptr<Entity> &item_entity, std::unique_ptr<Entity> &using_entity);
  bool addItem(std::unique_ptr<Entity> &a);

  Container(unsigned size);
  ~Container() {}

  std::vector<std::unique_ptr<Entity>> inv;
  //std::vector<Entity*> inv;
  unsigned size;

 private:

  
};

#endif
