#include "f_item.h"
#include "entity.h"
#include "f_container.h"
#include "f_mortal.h"
#include "gui.h"

bool Item::Use(std::unique_ptr<Entity> &item_entity, std::unique_ptr<Entity> &using_entity) {
	if ( using_entity->container ) {
	  Gui::LogMsg(item_entity->item->getMsg());
	  using_entity->container->removeItem(item_entity);
	  return true;
	}
	return false;
}
Healing::Healing(int amount, std::string _use_msg)
  : amount(amount), _use_msg(_use_msg){

}

bool Healing::Use(std::unique_ptr<Entity> &item_entity, std::unique_ptr<Entity> &using_entity){
  if ( using_entity->mortal ) {
    int amountHealed = using_entity->mortal->Heal(amount);
    if ( amountHealed > 0 ) {
      return Item::Use(item_entity,using_entity);
    }
  }
  return false;
  
}
