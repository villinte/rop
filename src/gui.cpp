#include "gui.h"
#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"

namespace Gui{
  std::vector<std::string > msgLog;
  void LogMsg(std::string str){
    msgLog.push_back(str);
  }

  void RenderGui(){
    // Draw lines, indicate GUI
    // top line
    engine.DrawLine(P(globals::FONT_W,globals::MAP_HEIGHT*globals::FONT_H+1), P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::MAP_HEIGHT*globals::FONT_H+1), White);
    // Left line
    engine.DrawLine(P(globals::FONT_W, globals::MAP_HEIGHT*globals::FONT_H+1), P(globals::FONT_W, globals::SCREEN_HEIGHT), White);
    // right line
    engine.DrawLine(P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::MAP_HEIGHT*globals::FONT_H+1), P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::SCREEN_HEIGHT), White);

    // Msg Log Separator
    engine.DrawLine(P(globals::MAP_WIDTH*globals::FONT_W/2-15*globals::FONT_W,globals::MAP_HEIGHT*globals::FONT_H+1), P(globals::MAP_WIDTH*globals::FONT_W/2-15*globals::FONT_W,globals::SCREEN_HEIGHT), White);
    
    // Draw msg log
    engine.printMsg(msgLog.back(), 2, globals::MAP_HEIGHT+2, globals::SCREEN_WIDTH/globals::FONT_W, Black);
    
    // Draw line, end of GUI
  }
  
}
