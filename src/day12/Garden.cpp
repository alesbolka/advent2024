#include "./day12.h"

namespace day12
{

using std::vector;
using std::string;
using helpers::point::Point;

Garden::Garden(vector<string> lines)
{
  std::map<Point, bool> regionMap;
  for (int yy = 0; yy < lines.size(); yy++)
  {
    for (int xx = 0; xx < lines[yy].size(); xx++)
    {
      Point current{ yy, xx };
      if (regionMap[current])
      {
        continue;
      }

      Region reg(current, lines);
      this->regions.push_back(reg);
      for (auto node : reg.nodes())
      {
        regionMap[node] = true;
      }
    }
  }
  std::cout << std::endl;
};

uint64_t Garden::fencePrice()
{
  uint64_t res = 0;
  for (auto region : regions)
  {
    res += region.fencePrice();
  }

  return res;
}

uint64_t Garden::discountedPrice()
{
  uint64_t res = 0;
  for (auto region : regions)
  {
    res += region.discountedPrice();
  }
  return res;
}

}