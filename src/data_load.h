#ifndef DATA_LOAD_H
#define DATA_LOAD_H

#include "tinyxml2.h"
#include <memory>
#include "entity.h"
#include <iostream>
#include <string>
#include <stdlib.h>
namespace dataLoad{
  
  void Init();

  extern tinyxml2::XMLDocument monsters;
  
  std::string getAttribute(std::string mon_name, std::string mon_element, std::string mon_attribute);
  
}


#endif
  
