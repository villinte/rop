#include "game.h"
#include "globals.h"
#include "sdl_wrapper.h"
#include "entity.h"
#include "map.h"
#include "f_ai.h"
#include "f_mortal.h"
#include "gui.h"

namespace Game{

  bool isRunning = false;
  sdlEngine sdl;

  std::unique_ptr<Entity> player = nullptr;
  
  void Init(){
    // Init player + player components
    std::unique_ptr<Entity> pEntity(new Entity(P(0,0), "Player", '@', White));
    player = std::move(pEntity);
    
    std::unique_ptr<Ai> pAi(new PlayerAi());
    player->ai = std::move(pAi);

    
    Map::cleanMap();
    Map::createMap();
    
    isRunning = true;
  }

  void runStartMenu(){
    // Do important stuff here.
  }

  void runGame(){
    
    while(isRunning){
      /* Handle Rendering
	 renderMap
	 renderGui
	 renderMonsters
	 renderPlayer	 
      */
      Render();
           
      
      /* Handle Game Logic
	 handleFov
	 handleCollisions
	 handleCombat
      */
      Tick();
    }
    
  }

  void Render(){
    sdl.clear();
    Map::renderMap();

    player->Render();
    Gui::RenderGui();
    sdl.flip();
  }

  void Input(){

  }
  
  void Tick(){
    player->Update();
  }

  void menuState(){

  }
  
}
