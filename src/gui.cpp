/* This whole shit needs to be seriously rewritten...
 * Too much hard coded values... Do better stuff?
 * Gui tied to state machine?
 */

#include "gui.h"
#include "sdl_wrapper.h"
#include "helper.h"
#include "game.h"
#include "entity.h"
#include "f_mortal.h"
#include "map.h"
#include <algorithm>
#include "debug_print.h"


namespace Gui{

  const int cmdStartY = g::SCREEN_HEIGHT/g::GLYPH_H + 13;
  
  int logUpdate = 0;
  std::vector<std::string > msgLog;

  void Init(){
    // Setup grid    
  }

  
  std::string cmdStr;
  void LogMsg(std::string str){
    msgLog.push_back(str);
    Debug::print("Logging: " + msgLog[msgLog.size()-1]);
    logUpdate = 2;
  }

  void LogMsgBeforeLast(std::string str){

    std::string lastMsg = msgLog.back();
    msgLog.erase(msgLog.end());
    msgLog.push_back(str);
    Debug::print("Log before last: " + msgLog[msgLog.size()-1]); 
    msgLog.push_back(lastMsg);
     
  }

  void AddCmdMsg(std::string str){
    cmdStr = str;
  }
  
  void ClearCmdMsg(){
    cmdStr.clear();
  }

  
  void showMsgLog(){
    io::clear();

    io::printMsg("Message Log. ESC will return you to the game.", 1, 0, g::SCREEN_WIDTH-1, Green);
    
    for(unsigned int i = 0; i < msgLog.size(); ++i){
      io::printMsg(msgLog[i], 1, 1+i, g::SCREEN_WIDTH-1, White);
    }
    io::flip();
    while(true){
      Keys key = io::Input();
      if(key == K_ESC)
	break;
    }
  }

  void showKillScreen(){
    io::clear();

    io::printMsg("You Died!", 30, 20, 20, Red);
    io::printMsg("Press Escape To... Escape", 30, 22, 30, Red);

    io::flip();
    while(true){
      Keys key = io::Input();
      if(key == K_ESC){
	Game::isRunning = false;
	break;
      }
    }
  }

  
  void RenderGui(){

    DrawOutlines();
    
    DrawMsgLog();
    
    DrawStats();

    io::flip();
    
  }

  void DrawMsgLog(){
    //    for(unsigned int i = 0; i < msgLog.size(); ++i){
    // io::printMsg(msgLog[i], 1, g::SCREEN_HEIGHT/g::GLYPH_H+4-i, g::SCREEN_WIDTH-1, White);
    //}
    //    io::printMsg(msgLog.back(), 2, g::SCREEN_HEIGHT/g::GLYPH_H+6, 33, Orange);

    int yPos = g::SCREEN_HEIGHT/g::GLYPH_H + 12;
    unsigned int logWidth = 50;
    unsigned int amountToShow = 9;
    for(unsigned int i = 0; i < amountToShow; ++i){

      if(msgLog.size() > i){
	if(msgLog[msgLog.size()-i-1].size() > logWidth && i < amountToShow)
	  i++;
	
	io::printMsg(msgLog[msgLog.size()-i-1], 2, yPos-i, logWidth, Orange);

      }
      
    }
    
    // Draw cmd msg
    io::printMsg(cmdStr, 2, cmdStartY, logWidth, Green);
  }

  void DrawStats(){
    // Render Player Stats
    renderComparedValue(P(43,34), Game::player->mortal->hp, Game::player->mortal->maxHp,
    			"HP: ", White);

    renderStringAndInt(P(43, 36), "Turn:",Game::turnCounter, White);

    // Render Dungeon Level
    renderStringAndInt(P(43, 38), "Dungeon Level:", Map::dungeonLevel, White);
    
  }

  void DrawOutlines(){

    // Draw lines, indicate GUI
    // top line
    io::DrawLine(P(g::FONT_W,g::MAP_HEIGHT*g::GLYPH_H+1),
		 P(g::MAP_WIDTH*g::FONT_W-g::FONT_W,
		   g::MAP_HEIGHT*g::GLYPH_H+1), White);
    // Left line
    io::DrawLine(P(g::FONT_W, g::MAP_HEIGHT*g::GLYPH_H+1),
		 P(g::FONT_W, g::SCREEN_HEIGHT), White);
    // right line
    io::DrawLine(P(g::MAP_WIDTH*g::FONT_W-g::FONT_W, g::MAP_HEIGHT*g::GLYPH_H+1),
		 P(g::MAP_WIDTH*g::FONT_W-g::FONT_W, g::SCREEN_HEIGHT), White);

    
    // Msg Log Separatorline
    int cmdSepx = g::MAP_WIDTH*g::FONT_W/2-4*g::FONT_W + 6*g::FONT_W;
    int cmdSepy = g::MAP_HEIGHT*g::GLYPH_H+1;
    io::DrawLine(P(cmdSepx,cmdSepy), P(cmdSepx,g::SCREEN_HEIGHT), White);
    
  }

  void renderStringAndInt(P p, std::string str, int num, cColor c){
    std::string temp = str + std::to_string(num);
    io::printMsg(temp, p.x, p.y, temp.length(), c);
  }
  
  void renderComparedValue(P p, int v1, int v2, std::string str, cColor c){
    std::string temp = str + std::to_string(v1) + "/" + std::to_string(v2);
    io::printMsg(temp,p.x,p.y,temp.length(),c );
    
  }

  void viewMode(){

    P crosshair;
    crosshair.x = Game::player->pos.x;
    crosshair.y = Game::player->pos.y;
    while(true){
      io::clear();
      Keys key = io::Input();
      if(key == K_ESC)
	break;

      if(key == K_LEFT){
	crosshair.x--;
      }
      else if(key == K_RIGHT){
	crosshair.x++;
      }
      else if(key == K_UP){
	crosshair.y--;
      }
      else if(key == K_DOWN){
	crosshair.y++;
      }

      Map::renderMap();
      // Render actors
      for(auto& a : Game::actors){
	if(Map::cells[a->pos.x][a->pos.y].isSeen)
	  a->Render();
      }
      Game::player->Render();
      RenderGui();
      io::drawClearRect(crosshair, Green);

      if(Map::cells[crosshair.x][crosshair.y].isSeen){
	// Draw look msg
	std::string msg;
	if(Game::getEntityDescription(P(crosshair)) == "No Entity"){
	  msg = "You see " + Map::cells[crosshair.x][crosshair.y]._description;
	}
	else{
	  msg = "You see " + Game::getEntityDescription(P(crosshair));
	}
	io::printMsg(msg, 2, cmdStartY, g::SCREEN_WIDTH/g::FONT_W, Green);
      }
      
      io::flip();
    }
  }

}
