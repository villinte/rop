#include "map_generate.h"
#include "globals.h"
#include "entity.h"
#include "helper.h"
#include <vector>
#include <memory>
#include "map.h"

namespace Map_Generator{

  void Generate(){
   
    
    
  }//Generate()

  void fillRect(int x_start, int y_start, int h, int w, char glyph){
    for(int  x = x_start; x < h; ++x){
      for(int y = y_start; y < w; ++y){
	Map::cells[x][y]._glyph = glyph;
      }
    }    
  }

  _DIR getWallDir(int x, int y){

    if(Map::cells[x][y]._glyph == '.'){
      if(Map::cells[x-1][y]._glyph == '#'){
	return WEST;
      }
      if(Map::cells[x+1][y]._glyph == '#'){
	return EAST;
      }
      if(Map::cells[x][y-1]._glyph == '#'){
	return NORTH;
      }
      if(Map::cells[x][y+1]._glyph == '#'){
	return SOUTH;
      }
    }
    return UNKNOWN;
  }

  void makeSquareRoom(int x, int y, _DIR wallDir){

  }
  
  void makeCorridor(int x, int y, _DIR wallDir){
        
    
  }
  
}
