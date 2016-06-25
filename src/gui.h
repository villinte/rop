#ifndef GUI_H
#define GUI_H
#include <string>
#include <vector>


namespace Gui{
  extern int logUpdate;
  extern std::vector<std::string > msgLog;
  extern std::string cmdStr;

  void AddCmdMsg(std::string str);
  void AddCmdMsg(std::string str1, std::string str2);
  void ClearCmdMsg();
  
  void LogMsg(std::string str);

  void showMsgLog();
  
  void RenderGui();
  
}


#endif
