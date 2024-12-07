#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include "./day06.h"


using std::vector;
using std::string;
using std::unordered_map;

namespace day06
{

Point rotate(Point current)
{
  if (current == LEFT)
  {
    return UP;
  }
  else if (current == UP)
  {
    return RIGHT;
  }
  else if (current == RIGHT)
  {
    return DOWN;
  }
  else if (current == DOWN)
  {
    return LEFT;
  }

  throw std::invalid_argument("Invalid Point passed to the rotate function " + std::to_string(current.y) + "," + std::to_string(current.x));
}

Map::Map(vector<std::string> lines)
{
  const string directionals = "^<>v";
  this->start = Point{ -1,-1 };
  this->walls = vector<vector<bool>>(
    lines.size(),
    vector<bool>(
      lines.size() > 0 ? lines[0].size() : 0,
      false
    )
  );

  for (int dy = 0; dy < lines.size(); dy++)
  {
    int yy = lines.size() - dy - 1;
    if (lines[yy].size() != this->walls[yy].size())
    {
      throw std::invalid_argument("line size mismatch: '" + lines[yy] + "'");
    }

    for (int xx = 0; xx < lines[yy].size(); xx++)
    {
      switch (lines[yy][xx])
      {
      case '#':
        this->walls[yy][xx] = true;
        break;
      case '<':
        this->start = Point{ yy, xx };
        this->direction = LEFT;
        break;
      case '>':
        this->start = Point{ yy, xx };
        this->direction = RIGHT;
        break;
      case '^':
        this->start = Point{ yy, xx };
        this->direction = UP;
        break;
      case 'v':
        this->start = Point{ yy, xx };
        this->direction = DOWN;
        break;
      default:
        break;
      }
    }
  }
};

inline bool Map::shouldCheckBlocker(
  Point node
)
{
  return !this->isOutOfBounds(node) && !this->isWall(node);
}

vector<Point> Map::findVisitedLocations(vector<Point>* blockers)
{
  vector<Point> res{};
  unordered_map<int64_t, bool> visited{};
  Point current(this->start);
  int size = this->walls[current.y].size();
  auto direction = this->direction;
  // std::cout << "start: " << current << std::endl;
  unordered_map<int64_t, bool> checkedBlockers{};

  int jj = 0;
  while (!this->isOutOfBounds(current))
  {
    if (this->isWall(current))
    {
      current -= direction;
      direction = rotate(direction);
    }
    else {
      // this->print(visited, direction, current);
      int nodeId = this->nodeId(current);
      if (blockers == nullptr && !visited.contains(nodeId)) {
        visited[nodeId] = true;
        res.push_back(current);
      }

      if (
        blockers != nullptr &&
        this->shouldCheckBlocker(current + direction)
      )
      {
        bool isRecursive = this->checkForRecursion(current, direction);
        if (isRecursive)
        {
          blockers->push_back(current + direction);
        }
      }
    }

    current += direction;
  }

  // if (blockers != nullptr)
  // {
  //   for (Point blocker : *blockers)
  //   {
  //     this->print(visited, Point{ -1,-1 }, Point{ -1,-1 }, &blocker);
  //   }
  // }

  return res;
}

inline bool Map::isWall(Point node)
{
  return !this->isOutOfBounds(node) && this->walls[node.y][node.x];
}

inline bool Map::isOutOfBounds(Point node)
{
  return node.y < 0 ||
    node.y >= this->walls.size() ||
    node.x < 0 ||
    node.x >= this->walls[node.y].size();
}

bool Map::checkForRecursion(Point start, Point direction)
{
  unordered_map<int64_t, bool> visited{};
  vector<int64_t> travelled{};
  Point current(start);
  Point fakeWall(start + direction);

  // this->print(visited, direction, current, &fakeWall);
  // std::cout << "checking recursion " << start << direction << std::endl;
  int ii = 0;

  while (!this->isOutOfBounds(current))
  {
    if (this->isWall(current) || current == fakeWall)
    {
      current -= direction;
      direction = rotate(direction);
      current += direction;
    }

    auto nodeId = this->nodeId(current, &direction);
    // this->print(visited, direction, current, &fakeWall);
    // std::cout << std::endl;

    if (std::find(travelled.begin(), travelled.end(), nodeId) != travelled.end())
    {
      return true;
    }

    travelled.push_back(nodeId);


    current += direction;
  }
  return false;
}


inline int64_t Map::nodeId(Point node, Point* direction)
{
  int64_t  res = 10 * (node.y * this->walls[0].size() + node.x);
  if (direction != nullptr) {
    if (*direction == LEFT)
    {
      res += 0;
    }
    else if (*direction == RIGHT)
    {
      res += 1;
    }
    else if (*direction == DOWN)
    {
      res += 2;
    }
    else if (*direction == RIGHT)
    {
      res += 3;
    }
  }
  return  res;
}

}
