#ifndef DAY_12
#define DAY_12

#include <algorithm>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include "../helpers/Point.h"

namespace day12
{
using helpers::point::Point;

/**
 *This is likely overengineered and I expect it won't be reusable for part 2, but I'm experimenting with C++ a bit
 */
class Region
{
public:
  Region(Point start, const std::vector<std::string>& grid);

  inline std::vector<Point> nodes() { return this->_nodes; };
  int64_t fencePrice();
protected:
  char plant;
  std::vector<Point> _nodes;
  std::map<Point, char> _walls;
};

class Garden
{
public:
  Garden(std::vector<std::string> lines);
  int64_t fencePrice();
protected:
  std::vector<Region> regions;
};

inline int64_t executor(int task, std::vector<std::string> input)
{
  Garden grdn(input);

  if (task == 1) {
    return grdn.fencePrice();
  }

  if (task == 2) {
    return -1;
  }

  return -1;
};


}

#endif
