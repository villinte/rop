#include "gui.h"
#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"

namespace Gui{
  std::vector<std::string > msgLog;
  std::string cmdStr;
  
  void LogMsg(std::string str){
    msgLog.push_back(str);
  }

  void AddCmdMsg(std::string str){
    cmdStr = str;
  }
  void ClearCmdMsg(){
    cmdStr = " ";
  }
  
  void RenderGui(){
    // Draw lines, indicate GUI
    // top line
    engine.DrawLine(P(globals::FONT_W,globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::MAP_HEIGHT*globals::GLYPH_H+1), White);
    // Left line
    engine.DrawLine(P(globals::FONT_W, globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::FONT_W, globals::SCREEN_HEIGHT), White);
    // right line
    engine.DrawLine(P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::SCREEN_HEIGHT), White);

    // CMD msg Separator
    engine.DrawLine(P(globals::MAP_WIDTH*globals::FONT_W/2-10*globals::FONT_W,globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::MAP_WIDTH*globals::FONT_W/2-10*globals::FONT_W,globals::SCREEN_HEIGHT), White);

    
    
    // Draw cmd msg
    engine.printMsg(cmdStr, 2, globals::SCREEN_HEIGHT/globals::GLYPH_H+4, globals::SCREEN_WIDTH/globals::FONT_W, Green);
    
    // Draw line, end of GUI
    engine.flip();
  }

}
