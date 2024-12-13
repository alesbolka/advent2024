#ifndef DAY_10
#define DAY_10

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "../helpers/Point.h"

namespace day10
{

using helpers::point::Point;

class Map
{
public:
  Map(std::vector<std::string> lines);
  uint64_t trailScore();
  uint64_t trailScoreV2();
protected:
  std::vector<std::string> grid;
  std::vector<Point> startNodes;
};

uint64_t task1(std::vector<std::string> lines);
uint64_t task2(std::vector<std::string> lines);

inline uint64_t executor(int task, std::vector<std::string> input)
{

  if (task == 1) {
    return task1(input);
  }

  if (task == 2) {
    return task2(input);
  }

  return -1;
};


}

#endif
