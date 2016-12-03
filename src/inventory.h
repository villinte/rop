#ifndef INVENTORY_H
#define INVENTORY_H
#include <memory>
#include "state.h"
#include <vector>
class Container;
class Entity;
class P;

class InventoryState : public State{
 public:
  InventoryState();
  void Init() override;
  void Draw() override;
  void Update() override;
  void Pause() override;
  void Resume() override;
  bool draw_overlayed() const{
    return true;
  }

 private:
  unsigned int selected;
  unsigned int amountItems;

};

namespace Inventory{

  void Show(std::unique_ptr<Container> &d);
  
}


#endif
