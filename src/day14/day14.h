#ifndef DAY_14
#define DAY_14

#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include "../helpers/helpers.h"
#include "../helpers/Point.h"

namespace day14
{
using helpers::point::Point;

class Guard
{
public:
  Point pos0;
  Point dir;

  inline Guard(Point startPos, Point direction)
  {
    pos0 = startPos;
    dir = direction;
  };
};

class Grid
{
public:
  int sizeY;
  int sizeX;

  Grid(std::vector<std::string> lines, int gridY, int gridX);
  uint64_t simulateMovement(int steps);
  uint64_t stepsToTree();
protected:
  std::vector<Guard> guards;
};

inline uint64_t executor(int task, std::vector<std::string> input)
{
  Grid grid(input, 103, 101);

  if (task == 1)
  {
    return grid.simulateMovement(100);
  }

  return grid.stepsToTree();
};
}

#endif
