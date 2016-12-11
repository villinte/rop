#include "map_gen.h"
#include "helper.h"
#include <iostream>
#include <algorithm>

namespace mapGen{
  
  char _map[globals::MAP_WIDTH][globals::MAP_HEIGHT];

  void init(){
    fillRect(R(P(0,0), P(globals::MAP_WIDTH, globals::MAP_HEIGHT)), '#');
    bool first = true;

    // player start pos
    P player_p;
    
    R prev;
    
    for(int i = 0; i < 13; ++i){
      // Room dimensions
      unsigned int max_w = 0;
      unsigned int max_h = 0;
      unsigned int min_w = 0;
      unsigned int min_h = 0;
    
      // Small or Big room?
      unsigned int bs = Rng::randInt(1, 100);
      if(bs < 80){
	max_w = 5;
	max_h = 5;
	min_w = 3;
	min_h = 3;
      }
      else{
	max_w = 10;
	max_h = 10;
	min_w = 6;
	min_h = 6;
      }
      R current;
      while(!buildRoom(current, Rng::randInt(1,globals::MAP_WIDTH-1), Rng::randInt(1,globals::MAP_HEIGHT-1),
		       Rng::randInt(min_w, max_w), Rng::randInt(min_h, max_h))){
	
      }
      
      if(first){
	bool check = false;
	while(!check){
	  int x = Rng::randInt(1, globals::MAP_WIDTH-1);
	  int y = Rng::randInt(1, globals::MAP_HEIGHT-1);
	  if(_map[x][y] == '.'){
	    check = true;
	    player_p.x = x;
	    player_p.y = y;
	  }
	}
	first = false;
      }
      else{
	createHorizontalTunnel(current.center(), prev.center());
	createVerticalTunnel(prev.center(), current.center());

	// chance to add monsters in the center of the room
	if(Rng::randInt(0,100) > 60){
	  unsigned int amountMonster = Rng::randInt(1,4);
	  createMonster(amountMonster, current.center());
	}
      }

	
      prev = current;	
	
    }
    // add player in first room
    _map[player_p.x][player_p.y] = '@';
    
    // add some cool doors

    for(int y = 0; y <= globals::MAP_HEIGHT; ++y){
      for(int x = 0; x <= globals::MAP_WIDTH; ++x){
	if(_map[x][y] == '.'){
	  if((_map[x+1][y] == '.' &&
	      _map[x-1][y] == '.' &&
	      _map[x+1][y+1] == '.' &&
	      _map[x+1][y-1] == '.' &&
	      (_map[x-1][y-1] == '.' || _map[x-1][y-1] == '#') &&
	      (_map[x-1][y+1] == '.' || _map[x-1][y+1] == '#') &&
	      _map[x][y-1] == '#' &&
	      _map[x][y+1] == '#')
	     || (_map[x+1][y] == '#' &&
		 _map[x-1][y] == '#' &&
		 _map[x+1][y+1] == '.' &&
		 (_map[x+1][y-1] == '.' || _map[x+1][y-1] == '#') &&
		 (_map[x-1][y-1] == '.' || _map[x-1][y-1] == '#') &&
		 _map[x-1][y+1] == '.' &&
		 _map[x][y-1] == '.' &&
		 _map[x][y+1] == '.')
	     || (_map[x+1][y] == '.' &&
		 _map[x-1][y] == '.' &&
		 (_map[x+1][y+1] == '.' || _map[x+1][y+1] == '#') &&
		 (_map[x+1][y-1] == '.' || _map[x+1][y-1] == '#') &&
		 _map[x-1][y-1] == '.' &&
		 _map[x-1][y+1] == '.' &&
		 _map[x][y-1] == '#' &&
		 _map[x][y+1] == '#')
	     || (_map[x+1][y] == '#' &&
		 _map[x-1][y] == '#' &&
		 (_map[x+1][y+1] == '.' || _map[x+1][y+1] == '.') &&
		 _map[x+1][y-1] == '.' &&
		 _map[x-1][y-1] == '.' &&
		 (_map[x-1][y+1] == '.' || _map[x-1][y+1] == '#') &&
		 _map[x][y-1] == '.' &&
		 _map[x][y+1] == '.')

	     ){
	    
	    _map[x][y] = '+';
	    
	  }
	}
      }

      
    }
    
  }
  
  void createHorizontalTunnel(P p1, P p2){
    for(int x = std::min(p1.x, p2.x); x <= std::max(p1.x, p2.x); ++x){
      _map[x][p2.y] = '.';
    }
  
  }

  void createVerticalTunnel(P p1, P p2){
    for(int y = std::min(p1.y, p2.y); y <= std::max(p1.y, p2.y); ++y){
      _map[p2.x][y] = '.';
    }
  }


  bool checkClearToBuild(const R &r){

    if(r.p0.y <= 0 || r.p1.y >= globals::MAP_HEIGHT ||
       r.p0.x <= 0 || r.p1.x >= globals::MAP_WIDTH){
      return false;
    }
    
    for(int y = r.p0.y; y <= r.p1.y; ++y){
      for(int x = r.p0.x; x <= r.p1.x; ++x){
	if(_map[x][y] == '.'){
	  return false;
	}
	
      }
    }
    return true;
  }
  
  bool buildRoom(R &r, unsigned int x, unsigned int y, unsigned int w, unsigned int h){

    
      
    unsigned int startX = x;
    unsigned int startY = y;
    unsigned int endX   = startX + w;
    unsigned int endY   = startY + h;

    if(!checkClearToBuild(R(P(startX, startY), P(endX, endY)))){
      return false;
    }
    r = R(P(startX, startY), P(endX, endY));
    
    fillRect(r, '.');
    return true;
  }
  
  void fillRect(const R &r, char c){
    for(int y = r.p0.y; y < r.p1.y; ++y){
      for(int x = r.p0.x; x < r.p1.x; ++x){
	_map[x][y] = c;
      }
    }
  
  }

  std::string getMapStr(){
    std::string str;

    for(int y = 0; y < globals::MAP_HEIGHT; ++y){
      for(int x = 0; x < globals::MAP_WIDTH; ++x){
	str.push_back(_map[x][y]);
      }
      str.push_back(';');
    }
    
    return str;
  }

  void createMonster(unsigned int a, P p){
    for(int i = 0; i < (int)a; ++i){
      if(i < 2)
	_map[p.x+i][p.y] = 'L';
      else
	_map[p.x][p.y+i] = 'L';
    }
    
  }

}
