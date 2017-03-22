#include "pathfinding.h"
#include <memory>
#include "map.h"
#include "game.h"
#include "entity.h"


namespace PF{

  int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
  int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};
  int map[g::MAP_WIDTH][g::MAP_HEIGHT];
  int closed_nodes_map[g::MAP_WIDTH][g::MAP_HEIGHT];
  int open_nodes_map[g::MAP_WIDTH][g::MAP_HEIGHT];
  int dir_map[g::MAP_WIDTH][g::MAP_HEIGHT];


  std::vector<P> findPath(const P &Start, const P &Finish, bool actorsBlocking){

    // If we want actors to be seen as non passable objects on the map.
    if(actorsBlocking){
      for(auto& a : Game::actors){
	if(a->_block == true)
	PF::map[a->pos.x][a->pos.y] = 1;
      }
    }
    
    for(int y = 0; y < g::MAP_HEIGHT; ++y){
      for(int x = 0; x < g::MAP_WIDTH; ++x){
	if(Map::cells[x][y]._glyph == '#'){
	  PF::map[x][y] = 1;
	}
	else{
	  PF::map[x][y] = 0;
	}
      }
    }

    std::vector<P> returnVec;

    std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    int pqi; // pq index
    std::unique_ptr<node> n0;
    std::unique_ptr<node> m0;
    int i, j, x, y, xdx, ydy;
    pqi=0;

    // reset the node maps
    for(y=0;y<g::MAP_HEIGHT;y++){
      for(x=0;x<g::MAP_WIDTH;x++){
	closed_nodes_map[x][y]=0;
	open_nodes_map[x][y]=0;
      }
    }

    // create the start node and push into list of open nodes
    std::unique_ptr<node> n_temp(new node(Start, 0, 0));
    n0 = std::move(n_temp);
    n0->updatePriority(Finish);
    pq[pqi].push(*n0);
    open_nodes_map[Start.x][Start.y]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty()){

      std::unique_ptr<node> n_temp2(new node(pq[pqi].top().getPos(),
					     pq[pqi].top().getLevel(),
					     pq[pqi].top().getPriority()));
      n0 = std::move(n_temp2);
	
      x=n0->getxPos(); y=n0->getyPos();

      pq[pqi].pop(); // remove the node from the open list
      open_nodes_map[x][y]=0;
      // mark it on the closed nodes map
      closed_nodes_map[x][y]=1;

      // quit searching when the goal state is reached
      //if((*n0).estimate(xFinish, yFinish) == 0)
      if(x == Finish.x && y == Finish.y){
	// generate the path from finish to start
	// by following the directions
	while(!(x == Start.x && y == Start.y)){
	  j=dir_map[x][y];
	  returnVec.push_back(P(x,y));
	  x+=dx[j];
	  y+=dy[j];
	}

	while(!pq[pqi].empty()) pq[pqi].pop();        
	return returnVec;
      }

      // generate moves (child nodes) in all possible directions
      for(i = 0; i < dir; i++){
	xdx = x + dx[i];
	ydy = y + dy[i];

	if(!(xdx < 0 || xdx > g::MAP_WIDTH-1 || ydy<0 || ydy > g::MAP_HEIGHT-1
	     || map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1)){
	  // generate a child node
	  std::unique_ptr<node> n_temp3(new node(P(xdx, ydy), n0->getLevel(), 
						 n0->getPriority()));
	  m0 = std::move(n_temp3);
	  m0->nextLevel(i);
	  m0->updatePriority(Finish);

	  // if it is not in the open list then add into that
	  if(open_nodes_map[xdx][ydy]==0){
	    open_nodes_map[xdx][ydy]=m0->getPriority();
	    pq[pqi].push(*m0);
	    // mark its parent node direction
	    dir_map[xdx][ydy]=(i+dir/2)%dir;
	  }
	  else if(open_nodes_map[xdx][ydy]>m0->getPriority()){
	    // update the priority info
	    open_nodes_map[xdx][ydy]=m0->getPriority();
	    // update the parent direction info
	    dir_map[xdx][ydy]=(i+dir/2)%dir;

	    // replace the node
	    // by emptying one pq to the other one
	    // except the node to be replaced will be ignored
	    // and the new node will be pushed in instead
	    while(!(pq[pqi].top().getxPos()==xdx && 
		    pq[pqi].top().getyPos()==ydy)){                
	      pq[1-pqi].push(pq[pqi].top());
	      pq[pqi].pop();       
	    }
	    pq[pqi].pop(); // remove the wanted node
                    
	    // empty the larger size pq to the smaller one
	    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
	    while(!pq[pqi].empty()){                
	      pq[1-pqi].push(pq[pqi].top());
	      pq[pqi].pop();       
	    }
	    pqi=1-pqi;
	    pq[pqi].push(*m0); // add the better node instead
	  }
	      
	}
      }
	
    }
    return returnVec; // no route found
    
    
  }
  
  
}
