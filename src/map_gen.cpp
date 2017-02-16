#include "map_gen.h"
#include "helper.h"
#include "debug_print.h"
#include <algorithm>
#include <cmath>
#include <list>
#include <vector>
#include <string>

// Values for bsp
const int MAX_NODE_SIZE = 18;
const int MIN_NODE_SIZE = 7;

bsp::bsp(int x, int y, int w, int h){
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
  leftNode = nullptr;
  rightNode = nullptr;
}

bool bsp::split(){
  if(rightNode != nullptr || leftNode != nullptr){
    return false;
  }

  bool splitH = Rng::randInt(0, 100) > 50;
  if( (w > h) && (w/h >= 1.25) ){
    splitH = false;
  }
  else if(h > w && (h / w >= 1.25)){
    splitH = true;
  } 

  int max = (splitH ? h : w) - MIN_NODE_SIZE;

  if(max <= MIN_NODE_SIZE){
    return false;
  }

  int split = Rng::randInt(MIN_NODE_SIZE, max);
  if(splitH){
    leftNode = new bsp(x,y,w,split);
    rightNode = new bsp(x,y+split,w,h-split);
  }
  else{
    leftNode = new bsp(x,y,split,h);
    rightNode = new bsp(x+split,y,w-split,h);
  }

  return true;
  
}



namespace mapGen{

  namespace {
    P player_p;
  }
  
  char _map[g::MAP_WIDTH][g::MAP_HEIGHT];
  std::vector<R*> rooms;
  std::vector<R*> connectors;
  std::list<bsp*> nodes;
  void init(){

    player_p = P(0,0);
    
    bsp* root = new bsp(1,1,g::MAP_WIDTH, g::MAP_HEIGHT);

    nodes.push_back(root);
    
    bool didSplit = true;

    while(didSplit){

      didSplit = false;

      for(auto& i : nodes){

	if(i->leftNode == nullptr && i->rightNode == nullptr){
	  if(i->w > MAX_NODE_SIZE || i->h > MAX_NODE_SIZE || Rng::randInt(0,100) > 25){

	    if(i->split()){
	      nodes.push_back(i->leftNode);
	      nodes.push_back(i->rightNode);
	      didSplit = true;
	    }

	  }
	
	}
      
      }
      
    }
    // These functions will create the actual map in the _map array.
    fillRect(R(P(0,0), P(g::MAP_WIDTH, g::MAP_HEIGHT)), '#');
    createRooms(root);  // Creates the rooms within the bsp nodes
    createConnection(); // Draws connections from each room
    for(auto i : rooms){
      fillRect(*i, '.');
    }

    // add player in a random room
    int pStartRoom = Rng::randInt(0,rooms.size());
    player_p = rooms[pStartRoom]->center();
    _map[player_p.x][player_p.y] = '@';

    // Add Doors
    addDoors();
    
  }
  
  void createRooms(bsp *n){
    if(n->leftNode != nullptr || n->rightNode != nullptr){
      if(n->leftNode != nullptr){
	createRooms(n->leftNode);
      }

      if(n->rightNode != nullptr){
	createRooms(n->rightNode);
      }
    
    }
    else{
      
      P roomSize = P(Rng::randInt(3, n->w - 2),
		     Rng::randInt(3, n->h - 2));

      P roomPos = P(Rng::randInt(1, n->w - roomSize.x - 1),
		    Rng::randInt(1, n->h - roomSize.y - 1));
    
      R *tempRoom = new R(n->x + roomPos.x, n->y + roomPos.y, n->x + roomPos.x + roomSize.x,
			  n->y + roomPos.y + roomSize.y);
      

      if(Rng::randInt(0,100) > 30)
	addMonster(tempRoom->center());
      
      mapGen::rooms.push_back(tempRoom);
    }      
  
  }
  
  void createConnection(){
    if(rooms.size() > 1){
      
      for(unsigned int i = 1; i < rooms.size(); ++i){
	createHorizontalTunnel(rooms[i-1]->center(), rooms[i]->center());
	createVerticalTunnel(rooms[i]->center(), rooms[i-1]->center());
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
  
  void fillRect(const R &r, char c){
    for(int y = r.p0.y; y < r.p1.y; ++y){
      for(int x = r.p0.x; x < r.p1.x; ++x){
	_map[x][y] = c;
      }
    }
  
  }

  void addDoors(){
      for(int y = 0; y <= g::MAP_HEIGHT; ++y){
	for(int x = 0; x <= g::MAP_WIDTH; ++x){
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
      // Remove some of the doors, for reasons...?
      for(int y = 0; y < g::MAP_HEIGHT; ++y){
	for(int x = 0; x < g::MAP_WIDTH; ++x){
	  if(_map[x][y] == '+' && Rng::randInt(0,100) > 60){
	    if(Rng::randInt(0,100) > 50){
	      _map[x][y] = '/';
	    }
	    else{
	      _map[x][y] = '.';
	    }
	  }
	}
      }
      
  } // addDoors

  std::string getMapStr(){
    std::string str;

    for(int y = 0; y < g::MAP_HEIGHT; ++y){
      for(int x = 0; x < g::MAP_WIDTH; ++x){
	str.push_back(_map[x][y]);
      }
      str.push_back(';');
    }
    
    return str;
  }

  void addMonster(P p){
    for(int i = 0; i < 3; ++i){
      if(i < 2)
	_map[p.x+i][p.y] = 'L';
      else
	_map[p.x][p.y+i] = 'L';
    }
    
  }
  
}
 
