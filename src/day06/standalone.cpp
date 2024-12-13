#include <map>
#include <stdexcept>
#include "./day06.h"


using std::string;
using std::vector;
using std::map;

namespace day06
{

inline Point rotate_point(Point pt)
{
  if (pt == LEFT)
  {
    return UP;
  }
  else if (pt == UP)
  {
    return RIGHT;
  }
  else if (pt == RIGHT)
  {
    return DOWN;
  }
  else if (pt == DOWN)
  {
    return LEFT;
  }

  throw std::invalid_argument("Invalid Point passed to the rotate function " + std::to_string(pt.y) + "," + std::to_string(pt.x));
}

bool in_map(Point pt, int sizeY, int sizeX)
{
  return pt.y >= 0 && pt.y < sizeY &&
    pt.x >= 0 && pt.x < sizeX;
}

void print_map(
  map<Point, bool>walls,
  Point position,
  Point direction,
  int sizeY,
  int sizeX
)
{
  for (int yy = 0; yy < sizeY; yy++)
  {
    for (int xx = 0; xx < sizeX; xx++)
    {
      Point pt = Point{ yy, xx };
      if (pt == position)
      {
        if (direction == LEFT) {
          std::cout << '<';
        }
        else if (direction == RIGHT) {
          std::cout << '>';
        }
        else if (direction == UP) {
          std::cout << '^';
        }
        else {
          std::cout << 'v';
        }
      }
      else if (walls[pt])
      {
        std::cout << '#';
      }
      else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

bool isRecursive(Point start, Point startDir, map<Point, bool> walls, int sizeY, int sizeX)
{
  // print_map(walls, start, startDir, sizeY, sizeX);
  map<Point, map<Point, bool>> steps{};
  Point current(start);
  Point direction(startDir);

  while (in_map(current, sizeY, sizeX))
  {
    Point next = current + direction;

    if (walls[next])
    {
      direction = direction.rotate();
      continue;
    }

    if (steps[current][direction])
    {
      return true;
    }

    steps[current][direction] = true;

    current = next;
  }

  return false;
}


uint64_t task2_v2(vector<string> lines)
{
  uint64_t res = 0;
  Point current{ -1, -1 };
  Point direction = UP;
  map<Point, bool>walls{};
  int sizeY = lines.size();
  int sizeX = lines[0].size();
  map<Point, bool>checked{};

  for (int yy = 0; yy < sizeY; yy++)
  {
    for (int xx = 0; xx < sizeX; xx++)
    {
      Point pt = Point(yy, xx);
      walls[pt] = lines[yy][xx] == '#';

      if (lines[yy][xx] == '^')
      {
        current = pt;
      }
    }
  }

  while (in_map(current, sizeY, sizeX))
  {
    // print_map(walls, current, direction, sizeY, sizeX);
    Point next = current + direction;
    if (walls[next]) {
      direction = direction.rotate();
      continue;
    }

    if (in_map(next, sizeY, sizeX) && !checked[next])
    {
      checked[next] = true;
      auto tmpWalls(walls);
      tmpWalls[next] = true;
      bool check = isRecursive(current, direction.rotate(), tmpWalls, sizeY, sizeX);
      if (check)
      {
        res++;
      }
    }

    current = next;
  }

  return res;
}

}