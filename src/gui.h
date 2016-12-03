#ifndef GUI_H
#define GUI_H
#include <string>
#include <vector>
#include "helper.h"
#include "globals.h"

namespace Gui{
  extern int logUpdate;
  extern std::vector<std::string > msgLog;
  extern std::string cmdStr;
    
  void Init();

  void AddCmdMsg(std::string str);
  void ClearCmdMsg();
  
  void LogMsg(std::string str);

  void showMsgLog();

  void showKillScreen();
  
  void RenderGui();

  void renderComparedValue(P p, int v1, int v2, std::string str, cColor c);

  void renderStringAndInt(P p, std::string str, int num, cColor c);

  void viewMode();
}


#endif
