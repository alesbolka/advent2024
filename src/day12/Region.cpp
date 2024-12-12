#include "./day12.h"

namespace day12
{

using std::vector;
using std::queue;
using std::map;
using std::string;
using helpers::point::Point;

const Point directions[4] = {
  helpers::point::directions::UP,
  helpers::point::directions::DOWN,
  helpers::point::directions::LEFT,
  helpers::point::directions::RIGHT,
};

Region::Region(Point start, const vector<string>& lines)
{
  _walls = map<Point, char>{};

  queue<Point> toProcess{ };
  toProcess.push(start);
  plant = lines[start.y][start.x];

  while (!toProcess.empty())
  {
    Point node = toProcess.front();
    toProcess.pop();
    _walls[node] = 4;
    _nodes.push_back(node);

    for (auto dir : directions)
    {
      Point neighbour = dir + node;
      if (
        neighbour.y < 0 || neighbour.y >= lines.size() ||
        neighbour.x < 0 || neighbour.x >= lines[neighbour.y].size()
      )
      {
        continue;
      }

      if (lines[neighbour.y][neighbour.x] == plant)
      {
        _walls[node]--;
        if (!_walls.contains(neighbour))
        {
          toProcess.push(neighbour);
          _walls[neighbour] = 4;
        }
      }
    }
  }
};

int64_t Region::fencePrice()
{
  int64_t res = 0;
  for (auto plot : _walls)
  {
    res += plot.second;
  }
  res *= _walls.size();

  // std::cout << "price for " << plant << " = " << res << std::endl;

  return res;
}

}