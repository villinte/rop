#ifndef DEBUG_PRINT_H
#define DEBUG_PRINT_H

#include <string>

namespace Debug{

  extern bool debugEnabled;

  void Init(bool Active);
  
  void print(std::string str);
  void printf(std::string str);
}

#endif
