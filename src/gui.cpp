/* This whole shit needs to be seriously rewritten...
 * Too much hard coded values... Do better stuff?
 * Gui tied to state machine?
 */

#include "gui.h"
#include "sdl_wrapper.h"
#include "globals.h"
#include "helper.h"
#include "game.h"
#include "entity.h"
#include "f_mortal.h"

namespace Gui{
  int logUpdate = 0;
  std::vector<std::string > msgLog;
  
  std::string cmdStr;
  void LogMsg(std::string str){
    msgLog.push_back(str);
    logUpdate = 2;
  }

  void AddCmdMsg(std::string str){
    cmdStr = str;
  }
  
  void ClearCmdMsg(){
    cmdStr.clear();
  }

  
  void showMsgLog(){
    Game::sdl.clear();

    Game::sdl.printMsg("Message Log. ESC will return you to the game.", 1, 0, globals::SCREEN_WIDTH-1, Green);
    
    for(unsigned int i = 0; i < msgLog.size(); ++i){
      Game::sdl.printMsg(msgLog[i], 1, 1+i, globals::SCREEN_WIDTH-1, White);
    }
    Game::sdl.flip();
    while(true){
      Keys key = Game::sdl.Input();
      if(key == K_ESC)
	break;
    }
  }

  void showKillScreen(){
    Game::sdl.clear();

    Game::sdl.printMsg("You Died!", 30, 20, 20, Red);
    Game::sdl.printMsg("Press Escape To... Escape", 30, 22, 30, Red);

    Game::sdl.flip();
    while(true){
      Keys key = Game::sdl.Input();
      if(key == K_ESC){
	Game::isRunning = false;
	break;
      }
    }
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
    int cmdSepx = globals::MAP_WIDTH*globals::FONT_W/2-5*globals::FONT_W;
    int cmdSepy = globals::MAP_HEIGHT*globals::GLYPH_H+1;
    Game::sdl.DrawLine(P(cmdSepx,cmdSepy), P(cmdSepx,globals::SCREEN_HEIGHT), White);

    // Draw cmd msg
    Game::sdl.printMsg(cmdStr, 2, globals::SCREEN_HEIGHT/globals::GLYPH_H+4, globals::SCREEN_WIDTH/globals::FONT_W, Green);
    

    // Render latest log msg
    if(logUpdate > 0){
      Game::sdl.printMsg(msgLog.back(), 2, globals::SCREEN_HEIGHT/globals::GLYPH_H+6, globals::MAP_WIDTH*globals::FONT_W/2-5*globals::FONT_W, Orange);
      logUpdate--;
    }
    if(logUpdate <= 0)
      logUpdate = 0;


    // Render Player Stats
    // HP
    
    renderComparedValue(P(36,34), Game::player->mortal->hp, Game::player->mortal->maxHp,
    			"HP: ", White);

    renderStringAndInt(P(36, 36), "Turn:",Game::turnCounter, White);
    
    Game::sdl.flip();
  }

  void renderStringAndInt(P p, std::string str, int num, cColor c){
    std::string temp = str + std::to_string(num);
    Game::sdl.printMsg(temp, p.x, p.y, temp.length(), c);
  }
  
  void renderComparedValue(P p, int v1, int v2, std::string str, cColor c){
    std::string temp = str + std::to_string(v1) + "/" + std::to_string(v2);
    Game::sdl.printMsg(temp,p.x,p.y,temp.length(),c );
    
  }

}

