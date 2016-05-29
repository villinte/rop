#ifndef GUI_H
#define GUI_H
#include <string>
#include <vector>

namespace Gui{

  extern std::vector<std::string > msgLog;
  
  void LogMsg(std::string str);
  
  void RenderGui();
  
};


#endif
