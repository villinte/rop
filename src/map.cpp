#include "map.h"
#include "game.h"
#include "sdl_wrapper.h"
#include "entity.h"
#include "f_mortal.h"
#include "f_actor.h"
#include "f_fighter.h"
#include "f_item.h"
#include "actor_factory.h"
#include "gui.h"
#include "map_gen.h"
#include "debug_print.h"
#include <iostream>

/*
 * Cell should be derived from entity... do smth about this.
 */

Cell::Cell(){
  pos = P(-1,-1);
  _glyph = ' ';
  _description = " ";
  _color = White;
  _block = false;
  isExplored = false;
  isSeen = false;
  lightLevel = 0;  
}

Cell::~Cell(){
}

void Cell::Reset(){
  pos.set(-1,-1);
  _glyph = ' ';
  _description = " ";
  _block = false;
  isExplored = false;
  isSeen = false;
  lightLevel = 0;
}
 
void Cell::Replace(Cell c){
  this->pos = c.pos;
  this->_glyph = c._glyph;
  this->_description = c._description;
  this->_block = c._block;
  this->isExplored = c.isExplored;
  this->isSeen = c.isSeen;
  this->lightLevel = c.lightLevel;
  this->_color = c._color;
}

Door::Door(bool open){
  _open = open;
  pos = P(-1,-1);
  if(!_open){
    _glyph = '+';
    _description = "a closed door.";
    _block = true;
  }
  else{
    _glyph = '/';
    _description = "an open door.";
    _block = false;
  }
  _color = Brown;
  isExplored = false;
  isSeen = false;
  lightLevel = 0;
}

Door::~Door(){
}


namespace Map{
  
  Cell cells[g::MAP_WIDTH][g::MAP_HEIGHT];

  int dungeonLevel;

  void Init(){
    dungeonLevel = 1;
  }
  
  void nextLevel(){
    Debug::print("nextLevel");
    dungeonLevel++;
    createMap();
  }
  
  void createMap(){
    cleanMap();
    std::string str =
      "1###############################################################################;"
      "########################.....................###################################;"
      "#############################................###################################;"
      "####################################.........###################################;"
      "###########################...............L...##################################;"
      "###################################................#############.....###########;"
      "##################################.................#############.L.#############;"
      "#####################..............................##############....###########;"
      "#.....................................######...........L..########..############;"
      "#######.......................!..!....#..!.#..............########..############;"
      "#######...............................#..@.#..............########..############;"
      "#######..........................!....##+###..............########..############;"
      "#######........................................................................#;"
      "##################+#############...............############################L.###;"
      "#################..############...............#############################L.###;"
      "################..#############................#############################.###;"
      "################.########################+##################################.###;"
      "##############...L####################...........L...L..L.....L...............##;"
      "#########.|....#..###################..L....####################################;"
      "###########.......###################.......####################################;"
      "########################################.#######################################;"
      "################################################################################;";
    mapGen::init();
    str = mapGen::getMapStr();
    int x = 0, y = 0;
    
    for(unsigned int i = 0; i < str.length() ;++i){
      if(str.at(i) != ';'){
	cells[x][y].pos = P(x,y);
	cells[x][y]._color = Grey; // temp;

	if(str.at(i) == '@'){
	  Game::player->pos = P(x,y); // set player position
	  cells[x][y]._glyph = '.';
	  cells[x][y]._description = "a floor tile.";
	}
	else if(str.at(i) == 'L'){

	  int randNr = Rng::randInt(0,100); 	  

	  std::unique_ptr<Entity> a
	    = actor_factory::make((randNr > 50) ? "Troll" : "Orc", P(x,y));
	  
	  bool dowespawn = false;
	  if(dungeonLevel >= a->_spawnUpperLimit && dungeonLevel <= a->_spawnLowerLimit ){
	    dowespawn = true;
	  }
	  else{
	    dowespawn = false;
	  }

	  
	  std::string str = "Spawned " + a->_name;
	  Debug::print(str);
	  if(dowespawn){
	    Game::actors.emplace_back(std::move(a));
	  }
	  cells[x][y]._glyph = '.';
	  cells[x][y]._description = "a floor tile.";
	}

	else if(str.at(i) == '!'){
	  std::unique_ptr<Entity> potion(new Entity(P(x,y), "Healing Potion",
						    str.at(i), Red, "a healing potion."));
	  
	  Item* pHealing(new Healing(10, "You drank a healing potion."));
	  
	  potion->item = pHealing;
	  
	  Game::actors.emplace_back(std::move(potion));
	  
	  cells[x][y]._glyph = '.';
	  cells[x][y]._description = "a floor tile.";
	}

	else if(str.at(i) == '|'){
	  std::unique_ptr<Entity> dagger(new Entity(P(x,y), "Dagger",
						    str.at(i), Grey, "a dagger."));
	  Item* pWeapon(new Weapon(3, "You wield a dagger."));
	  dagger->item = pWeapon;
	  Game::actors.emplace_back(std::move(dagger));
	  cells[x][y]._glyph = '.';
	  cells[x][y]._description = "a floor tile.";
					 
	}	
	else{
	  cells[x][y]._glyph = str.at(i);
	}
	
	if(str.at(i) == '+'){
	  Door temp(false);
	  temp.pos.set(x,y);
	  temp._description = "a closed door.";
	  cells[x][y].Replace(temp);
	  
	}
	if(str.at(i) == '/'){
	  Door temp(true);
	  temp._description = "an open door.";
	  temp.pos.set(x,y);
	  cells[x][y].Replace(temp);
	  	
	}
	
	if(str.at(i) == '#'){
	  cells[x][y]._block = true;
	  cells[x][y]._description = "a wall.";
	}
	if(str.at(i) == '.'){
	  cells[x][y]._block = false;
	  cells[x][y]._description = "a floor tile.";
	}
	if(str.at(i) == '<'){
	  std::unique_ptr<Entity> stairs(new Entity(P(x,y), "Stairs",
						    str.at(i), Gold, "stairs leading down."));

	  Game::actors.emplace_back(std::move(stairs));
	  cells[x][y]._glyph = '.';
	  cells[x][y]._description = "a floor tile.";
	}
	
	x++;
      }
      else{
	y++;
	x=0;
      }
      
    }
    
    computeFov();
  } // createMap


  void cleanMap(){
    
    for(int x = 0; x < g::MAP_WIDTH; ++x){
      for(int y = 0; y < g::MAP_HEIGHT; ++y){
	cells[x][y].Reset();
	cells[x][y].pos = P(x,y);
      }
    }
    Game::clearActors();
    
  }

  void clearVision(){
    for(int x = 0; x < g::MAP_WIDTH; ++x){
      for(int y = 0; y < g::MAP_HEIGHT; ++y){
	cells[x][y].isSeen = false;
	cells[x][y].lightLevel = 0;
      }
    }
  }
  int VIEW_RADIUS_1 = 5;
  int VIEW_RADIUS_2 = 7;
  int VIEW_RADIUS_3 = 9;
  void computeFov(){
    P p(Game::player->pos.x, Game::player->pos.y);
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
    ox = (float)Game::player->pos.x+0.5f;
    oy = (float)Game::player->pos.y+0.5f;
    // radius 1
    for(i=0;i<VIEW_RADIUS_1;i++){
      cells[(int)ox][(int)oy].isSeen = true;
      cells[(int)ox][(int)oy].lightLevel = 1;
      cells[(int)ox][(int)oy].isExplored = true;
      if(cells[(int)ox][(int)oy]._block)
	return;
      if((int)ox >= g::MAP_WIDTH-1 || (int)oy >= g::MAP_HEIGHT-1  ||
	 (int)ox <= 0 || (int)oy <= 0)
	return;
      ox+=x;
      oy+=y;
    };
    // radius 2
    for(i=VIEW_RADIUS_1;i<VIEW_RADIUS_2;i++){
      cells[(int)ox][(int)oy].isSeen = true;
      cells[(int)ox][(int)oy].lightLevel = 2;
      cells[(int)ox][(int)oy].isExplored = true;
      if(cells[(int)ox][(int)oy]._block)
	return;
      if((int)ox >= g::MAP_WIDTH-1 || (int)oy >= g::MAP_HEIGHT-1 ||
	 (int)ox <= 0 || (int)oy <= 0)
	return;
      ox+=x;
      oy+=y;
    };
    // radius 3
    for(i=VIEW_RADIUS_2;i<VIEW_RADIUS_3;i++){
      cells[(int)ox][(int)oy].isSeen = true;
      cells[(int)ox][(int)oy].lightLevel = 3;
      cells[(int)ox][(int)oy].isExplored = true;
      if(cells[(int)ox][(int)oy]._block)
	return;

      if((int)ox >= g::MAP_WIDTH-1 || (int)oy >= g::MAP_HEIGHT-1 ||
	 (int)ox <= 0 || (int)oy <= 0)
	return;
      
      ox+=x;
      oy+=y;
    };
    
  }
  
  void renderMap(){
    for(int x = 0; x < g::MAP_WIDTH; x++){
      for(int y = 0; y < g::MAP_HEIGHT; y++){
	// Line of sight
	cColor temp;
	temp.r = 0;
	temp.g = 0;
	temp.b = 0;
	if(cells[x][y].lightLevel == 1){

	  temp.r = cells[x][y]._color.r;
	  temp.g = cells[x][y]._color.g;
	  temp.b = cells[x][y]._color.b;
	}
	else if(cells[x][y].lightLevel == 2){

	  temp.r = cells[x][y]._color.r/2;
	  temp.g = cells[x][y]._color.g/2;
	  temp.b = cells[x][y]._color.b/2;;
	}
	else if(cells[x][y].lightLevel == 3){

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
	io::renderGlyph(cells[x][y]._glyph, cells[x][y].pos.x, cells[x][y].pos.y, temp);
      }
    }

  }

  void openDoor(P pos){
    if(cells[pos.x][pos.y]._glyph == '+'){
      cells[pos.x][pos.y]._glyph = '/';
      cells[pos.x][pos.y]._block = false;
      cells[pos.x][pos.y]._description = "an open door.";
      Gui::LogMsg("I open a door.");
    }
  }

  bool closeDoor(P pos){
    bool success = false;
    _DIR dir = pickDir();
    if(dir == SOUTH){
      // south
      if(cells[pos.x][pos.y+1]._glyph == '/'){
	cells[pos.x][pos.y+1]._glyph = '+';
	cells[pos.x][pos.y+1]._block = true;
	cells[pos.x][pos.y]._description = "a closed door.";
	Gui::LogMsg("I close a door.");
	success = true;
      }
    }
    else if(dir == NORTH){
      // North
      if(cells[pos.x][pos.y-1]._glyph == '/'){
	cells[pos.x][pos.y-1]._glyph = '+';
	cells[pos.x][pos.y-1]._block = true;
	cells[pos.x][pos.y]._description = "a closed door.";
	Gui::LogMsg("I close a door.");
	success = true;
      }
    }
    else if(dir == EAST){
      // east
      if(cells[pos.x+1][pos.y]._glyph == '/'){
	cells[pos.x+1][pos.y]._glyph = '+';
	cells[pos.x+1][pos.y]._block = true;
	cells[pos.x][pos.y]._description = "a closed door.";
	Gui::LogMsg("I close a door.");
	success = true;
      }
    }
    else if(dir == WEST){
      // west
      if(cells[pos.x-1][pos.y]._glyph == '/'){
	cells[pos.x-1][pos.y]._glyph = '+';
	cells[pos.x-1][pos.y]._block = true;
	cells[pos.x][pos.y]._description = "a closed door.";
	Gui::LogMsg("I close a door.");
	success = true;
      }
    }
    if(success == true){
      computeFov();
      return true;
    }
    return false;
  }

  _DIR pickDir(){
    Gui::AddCmdMsg("Which direction?");
    Gui::RenderGui();
    _DIR direction;
    Keys dir = K_UNKNOWN;
    while(dir == K_UNKNOWN){
      dir = io::Input();
      if(dir == K_DOWN){
	// south
	direction = SOUTH;
      }
      else if(dir == K_UP){
	// North
	direction = NORTH;
      }
      else if(dir == K_RIGHT){
	// east
	direction = EAST;
      }
      else if(dir == K_LEFT){
	// west
	direction =WEST;
      }
      else if(dir == K_ESC)
	break;
      else{
	dir = K_UNKNOWN;
	direction = UNKNOWN;
      }
    }
    Gui::ClearCmdMsg();
    return direction;
  }

  
}
