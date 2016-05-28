#include "map.h"
#include "sdl_wrapper.h"
#include <iostream>
#include "game.h"
#include "actor.h"
#include <cmath>

Cell::Cell(){
  pos = P(-1,-1);
  _glyph = ' ';
  _color = White;
  isBlocking = false;
  isExplored = false;
  isSeen = false;
  playerLos = false;
}

Cell::~Cell(){

}

void Cell::Reset(){
  pos.set(-1,-1);
  _glyph = ' ';
  isBlocking = false;
  isExplored = false;
  isSeen = false;
  playerLos = false;
}

namespace Map{
  Cell cells[globals::MAP_WIDTH][globals::MAP_HEIGHT];
  
  void createMap(){
    std::string str =
      "1###############################################################################;"
      "########################......@..............###################################;"
      "#############################................###################################;"
      "####################################.........###################################;"
      "###########################..................###################################;"
      "###################################................#############################;"
      "##################################.................#############################;"
      "#####################..............................#############################;"
      "#.........................................................######################;"
      "#######...................................................######################;"
      "#######..................................@................######################;"
      "#######...................................................######################;"
      "#######........................................................................#;"
      "##################/#############................############################.###;"
      "#################..############................#############################.###;"
      "################..#############................#############################.###;"
      "################.########################+##################################.###;"
      "##############...####################.........................................##;"
      "#########......#..###################.......####################################;"
      "###########.......###################.......####################################;"
      "########################################.#######################################;"
      "########################################.#######################################;";
    
    int x = 0, y = 0;
    
    for(unsigned int i = 0; i < str.length() ;++i){
      if(str.at(i) != ';'){
	cells[x][y].pos = P(x,y);
	cells[x][y]._color = Black; // temp;

	if(str.at(i) == '@'){
	  game.player->pos = P(x,y); // set player position
	  cells[x][y]._glyph = '.';
	}
	else{
	  cells[x][y]._glyph = str.at(i);
	}
	
	if(str.at(i) == '+'){
	  cells[x][y]._color = Brown;
	  cells[x][y].isBlocking = true;
	}
	if(str.at(i) == '/'){
	  cells[x][y]._color = Brown;
	  cells[x][y].isBlocking = false;
	}

	if(str.at(i) == '#'){
	  cells[x][y].isBlocking = true;
	}
	x++;
      }
      else{
	y++;
	x=0;
      }
      
    }
    computeFov();
  }

  void cleanMap(){
    
    for(int x = 0; x < globals::MAP_WIDTH; ++x){
      for(int y = 0; y < globals::MAP_HEIGHT; ++y){
	cells[x][y].Reset();
	cells[x][y].pos = P(x,y);
      }
    }
    
  }

  void clearVision(){
    for(int x = 0; x < globals::MAP_WIDTH; ++x){
      for(int y = 0; y < globals::MAP_HEIGHT; ++y){
	cells[x][y].playerLos = 0;
      }
    }
  }
  int VIEW_RADIUS_1 = 5;
  int VIEW_RADIUS_2 = 7;
  int VIEW_RADIUS_3 = 9;
  void computeFov(){
    P p(game.player->pos.x, game.player->pos.y);
    float x = p.x;
    float y = p.y;
    int i;
    clearVision();
    for(i=0;i<360;i++){
      x=cos((float)i*0.01745f);
      y=sin((float)i*0.01745f);
      doFov(x,y);
    } 
  }

  void doFov(float x, float y){
    int i;
    float ox, oy;
    ox = (float)game.player->pos.x+0.5f;
    oy = (float)game.player->pos.y+0.5f;
    // radius 1
    for(i=0;i<VIEW_RADIUS_1;i++){
      cells[(int)ox][(int)oy].playerLos = 1;
      cells[(int)ox][(int)oy].isExplored = true;
      if(cells[(int)ox][(int)oy].isBlocking)
	return;
      if((int)ox >= globals::MAP_WIDTH-1 || (int)oy >= globals::MAP_HEIGHT-1)
	return;
      ox+=x;
      oy+=y;
    };
    // radius 2
    for(i=VIEW_RADIUS_1;i<VIEW_RADIUS_2;i++){
      cells[(int)ox][(int)oy].playerLos = 2;
      cells[(int)ox][(int)oy].isExplored = true;
      if(cells[(int)ox][(int)oy].isBlocking)
	return;
      if((int)ox >= globals::MAP_WIDTH-1 || (int)oy >= globals::MAP_HEIGHT-1)
	return;
      ox+=x;
      oy+=y;
    };
    // radius 3
    for(i=VIEW_RADIUS_2;i<VIEW_RADIUS_3;i++){
      cells[(int)ox][(int)oy].playerLos = 3;
      cells[(int)ox][(int)oy].isExplored = true;
      if(cells[(int)ox][(int)oy].isBlocking)
	return;

      if((int)ox >= globals::MAP_WIDTH-1 || (int)oy >= globals::MAP_HEIGHT-1)
	return;
      
      ox+=x;
      oy+=y;
    };
    
  }
  
  void renderMap(){
    for(int x = 0; x < globals::MAP_WIDTH; x++){
      for(int y = 0; y < globals::MAP_HEIGHT; y++){
	// Line of sight
	cColor temp;
	temp.r = 0;
	temp.g = 0;
	temp.b = 0;
	if(cells[x][y].playerLos == 1){

	  temp.r = cells[x][y]._color.r;
	  temp.g = cells[x][y]._color.g;
	  temp.b = cells[x][y]._color.b;
	}
	else if(cells[x][y].playerLos == 2){

	  temp.r = cells[x][y]._color.r/2;
	  temp.g = cells[x][y]._color.g/2;
	  temp.b = cells[x][y]._color.b/2;;
	}
	else if(cells[x][y].playerLos == 3){

	  temp.r = cells[x][y]._color.r/3;
	  temp.g = cells[x][y]._color.g/3;
	  temp.b = cells[x][y]._color.b/3;
	}
	// explored
	else if(cells[x][y].isExplored){
	  
	  temp.r = cells[x][y]._color.r/4;
	  temp.g = cells[x][y]._color.g/4;
	  temp.b = cells[x][y]._color.b/4;
	}
	engine.renderChar(cells[x][y]._glyph, cells[x][y].pos.x, cells[x][y].pos.y, temp);
      }
    }

  }
  
  int spawnMonsters(){
    return 0;
  }


  void openDoor(P pos){
    if(cells[pos.x][pos.y]._glyph == '+'){
      cells[pos.x][pos.y]._glyph = '/';
      cells[pos.x][pos.y].isBlocking = false;
    }
  }

  void closeDoor(P pos){
    // south
    if(cells[pos.x][pos.y+1]._glyph == '/'){
      cells[pos.x][pos.y+1]._glyph = '+';
      cells[pos.x][pos.y+1].isBlocking = true;
    }
    // North
    else if(cells[pos.x][pos.y-1]._glyph == '/'){
      cells[pos.x][pos.y-1]._glyph = '+';
      cells[pos.x][pos.y-1].isBlocking = true;
    }
    // east
    else if(cells[pos.x+1][pos.y]._glyph == '/'){
      cells[pos.x+1][pos.y]._glyph = '+';
      cells[pos.x+1][pos.y].isBlocking = true;
    }
    // west
    else if(cells[pos.x-1][pos.y]._glyph == '/'){
      cells[pos.x-1][pos.y]._glyph = '+';
      cells[pos.x-1][pos.y].isBlocking = true;
    }
  }
  
} //namespace Map
