#include "./day10.h"
#include "../helpers/Point.h"

using std::map;
using std::string;
using std::vector;

namespace day10
{

Map::Map(vector<string> data)
{
  grid = data;
  for (int yy = 0; yy < grid.size(); yy++)
  {
    for (int xx = 0; xx < grid[yy].size(); xx++)
    {
      if (grid[yy][xx] == '0')
      {
        startNodes.push_back(Point{ yy, xx });
      }
    }
  }
}


uint64_t Map::trailScore()
{
  uint64_t res = 0;
  vector<Point> directions{
    helpers::point::directions::LEFT,
    helpers::point::directions::UP,
    helpers::point::directions::RIGHT,
    helpers::point::directions::DOWN,
  };
  map<Point, map<Point, char>> interests{};
  bool hasNew = startNodes.size() > 0;
  for (auto node : startNodes)
  {
    interests[node][node] = '0';
  }

  map<Point, map<Point, char>> results{};

  while (hasNew)
  {
    hasNew = false;
    for (auto trailHead : interests)
    {
      map<Point, char> newInterests{};
      for (auto node : trailHead.second)
      {
        for (auto dir : directions)
        {
          Point neighbour = node.first + dir;
          // separate if just because of debugging purposes
          if (
            neighbour.y < 0 || neighbour.y >= grid.size() ||
            neighbour.x < 0 || neighbour.x >= grid[neighbour.y].size()
          )
          {
            continue;
          }

          if (grid[neighbour.y][neighbour.x] == (node.second + 1))
          {
            if (grid[neighbour.y][neighbour.x] == '9' && !newInterests[neighbour])
            {
              results[trailHead.first][neighbour] = true;
            }
            else {
              hasNew = true;
              newInterests[neighbour] = grid[neighbour.y][neighbour.x];
            }
          }
        }
      }

      interests[trailHead.first] = newInterests;
    }
  }

  for (auto trailHead : results)
  {
    res += trailHead.second.size();
  }

  return res;
}

uint64_t Map::trailScoreV2()
{
  uint64_t res = 0;
  vector<Point> directions{
    helpers::point::directions::LEFT,
    helpers::point::directions::UP,
    helpers::point::directions::RIGHT,
    helpers::point::directions::DOWN,
  };

  map<Point, int> nodesToCheck{};
  for (auto node : startNodes)
  {
    nodesToCheck[node] = 1;
  }

  for (char expectedVal = '1'; expectedVal <= '9'; expectedVal++)
  {
    map<Point, int> newNodesToCheck{};

    for (auto beingChecked : nodesToCheck)
    {
      for (auto dir : directions)
      {
        Point neighbour = beingChecked.first + dir;
        if (
            neighbour.y < 0 || neighbour.y >= grid.size() ||
            neighbour.x < 0 || neighbour.x >= grid[neighbour.y].size()
          )
        {
          continue;
        }

        if (grid[neighbour.y][neighbour.x] == expectedVal)
        {
          if (expectedVal == '9')
          {
            res += beingChecked.second;
          }
          else {
            newNodesToCheck[neighbour] += beingChecked.second;
          }
        }
      }
    }

    nodesToCheck = newNodesToCheck;
  }

  return res;
}

}