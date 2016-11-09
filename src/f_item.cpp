#include "f_item.h"
#include "entity.h"
#include "f_container.h"
#include "f_mortal.h"


bool Item::Use(Entity &item_entity, Entity &using_entity) {
	if ( using_entity.container ) {
		using_entity.container->removeItem(item_entity);
		//delete &item_entity;
		return true;
	}
	return false;
}
Healing::Healing(int amount) : amount(amount){

}

bool Healing::Use(Entity &item_entity, Entity &using_entity){
  if ( using_entity.mortal ) {
    int amountHealed = using_entity.mortal->Heal(amount);
    if ( amountHealed > 0 ) {
      return Item::Use(item_entity,using_entity);
    }
  }
  return false;
  
}
