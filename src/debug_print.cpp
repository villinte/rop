#include "debug_print.h"

#include <iostream>

namespace Debug{
  bool debugEnabled;

  void Init(bool Active){
    debugEnabled = Active;
  }

  void print(std::string str){

    if(debugEnabled){
      std::cout << str << std::endl;
    }
    
  }

  void printf(std::string str){
    if(debugEnabled){
      std::cout << str;
    }
  }
  
}
