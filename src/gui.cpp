#include "gui.h"
#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"
#include "game.h"

namespace Gui{
  std::vector<std::string > msgLog;
  std::string cmdStr;
  void LogMsg(std::string str){
    msgLog.push_back(str);
  }

  void AddCmdMsg(std::string str){
    cmdStr = str;
  }
  void AddCmdMsg(std::string str1, std::string str2){
    cmdStr = str1 + str2;
  }
  void ClearCmdMsg(){
    cmdStr = " ";
  }
  
  void RenderGui(){
    // Draw lines, indicate GUI
    // top line
    Game::sdl.DrawLine(P(globals::FONT_W,globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::MAP_HEIGHT*globals::GLYPH_H+1), White);
    // Left line
    Game::sdl.DrawLine(P(globals::FONT_W, globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::FONT_W, globals::SCREEN_HEIGHT), White);
    // right line
    Game::sdl.DrawLine(P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::MAP_WIDTH*globals::FONT_W-globals::FONT_W, globals::SCREEN_HEIGHT), White);

    // CMD msg Separator
    Game::sdl.DrawLine(P(globals::MAP_WIDTH*globals::FONT_W/2-10*globals::FONT_W,globals::MAP_HEIGHT*globals::GLYPH_H+1), P(globals::MAP_WIDTH*globals::FONT_W/2-10*globals::FONT_W,globals::SCREEN_HEIGHT), White);
    
    // Draw cmd msg
    Game::sdl.printMsg(cmdStr, 2, globals::SCREEN_HEIGHT/globals::GLYPH_H+4, globals::SCREEN_WIDTH/globals::FONT_W, Green);
    
    Game::sdl.flip();
  }

}
