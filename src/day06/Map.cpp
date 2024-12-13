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
  unordered_map<uint64_t, bool>* alreadyChecked,
  Point node,
  Point direction
)
{
  auto next = node + direction;
  if (this->isOutOfBounds(next) || this->isWall(next))
  {
    return false;
  }

  auto blockerId = this->nodeId(next);
  bool haveCheckedAlready = (*alreadyChecked)[blockerId];
  (*alreadyChecked)[blockerId] = true;

  return !haveCheckedAlready;
}

vector<Point> Map::findVisitedLocations(vector<Point>* blockers)
{
  vector<Point> res{};
  unordered_map<uint64_t, bool> visited{};
  Point current(this->start);
  int size = this->walls[current.y].size();
  auto direction = this->direction;
  // std::cout << "start: " << current << std::endl;
  unordered_map<uint64_t, bool> checkedBlockers{};

  while (!this->isOutOfBounds(current))
  {
    if (this->isWall(current))
    {
      current -= direction;
      direction = rotate(direction);
      current += direction;
    }

    // this->print(visited, direction, current);
    int nodeId = this->nodeId(current);
    if (blockers == nullptr && !visited.contains(nodeId)) {
      visited[nodeId] = true;
      res.push_back(current);
    }

    if (
      blockers != nullptr &&
      this->shouldCheckBlocker(&checkedBlockers, current, direction)
    )
    {
      bool isRecursive = this->checkForRecursion(current, direction);
      if (isRecursive)
      {
        blockers->push_back(current + direction);
      }
    }

    current += direction;
  }

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
  unordered_map<uint64_t, bool> visited{};
  unordered_map<uint64_t, bool> travelled{};
  Point current(start);
  Point fakeWall(start + direction);

  // this->print(visited, direction, current, &fakeWall);
  // std::cout << "checking recursion " << start << direction << std::endl;

  while (!this->isOutOfBounds(current))
  {
    if (this->isWall(current) || current == fakeWall)
    {
      current -= direction;
      direction = rotate(direction);
      current += direction;
    }

    auto nodeId = this->nodeId(current, &direction);

    if (travelled[nodeId])
    {
      return true;
    }

    travelled[nodeId] = true;

    current += direction;
  }
  return false;
}


inline uint64_t Map::nodeId(Point node, Point* direction)
{
  uint64_t  res = 10 * (node.y * this->walls[0].size() + node.x);
  if (direction != nullptr) {
    if (*direction == LEFT)
    {
      res += 1;
    }
    else if (*direction == RIGHT)
    {
      res += 2;
    }
    else if (*direction == DOWN)
    {
      res += 3;
    }
    else if (*direction == UP)
    {
      res += 4;
    }
  }
  return  res;
}

}
