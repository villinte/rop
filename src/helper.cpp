#include "helper.h"

namespace Rng{
  std::random_device rd;
  std::mt19937 mt(rd());

  int randInt(int ll, int ul){
    std::uniform_real_distribution<double> dist(ll,ul);
    return dist(mt);
  }
}
