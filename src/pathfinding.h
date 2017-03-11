#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <math.h>
#include <ctime>
#include <string>
#include "globals.h"
#include "helper.h"

static const int dir = 8;

class node
{
  // current position
  P pos;
  // total distance already travelled to reach the node
  int level;
  // priority=level+remaining distance estimate
  int priority;  // smaller: higher priority

 public:
  node(P p, int d, int pr) 
    {pos = p; level=d; priority = pr;}

  P getPos() const {return pos; }
  int getxPos() const {return pos.x;}
  int getyPos() const {return pos.y;}
  int getLevel() const {return level;}
  int getPriority() const {return priority;}
  
  void updatePriority(const P &dest){
    priority=level+estimate(dest)*10; //A*
  }

  // give better priority to going strait instead of diagonally
  void nextLevel(const int & i) // i: direction
  {
    level+=(dir==8?(i%2==0?10:14):10);
  }
        
  // Estimation function for the remaining distance to the goal.
  const int &estimate(const P &dest){
    static int xd, yd, d;
    xd=dest.x-pos.x;
    yd=dest.y-pos.y;         
    
    // Euclidian Distance
    d=static_cast<int>(sqrt(xd*xd+yd*yd));

    return(d);
  }
};

// Determine priority (in the priority queue)
inline bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

struct pfNode{

public:
  P p;
  bool Closed;
  int Value;
  
};

namespace PF{
  extern int n;
  extern int m;
  extern int dx[dir];
  extern int dy[dir];
  extern int map[g::MAP_WIDTH][g::MAP_HEIGHT];
  extern int closed_nodes_map[g::MAP_WIDTH][g::MAP_HEIGHT];
  extern int open_nodes_map[g::MAP_WIDTH][g::MAP_HEIGHT];
  extern int dir_map[g::MAP_WIDTH][g::MAP_HEIGHT];
  std::string pathFind( const P & Start, const P & Finish);
}



#endif
