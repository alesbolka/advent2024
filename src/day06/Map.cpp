#include <stdexcept>
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

vector<Point> Map::findVisitedLocations()
{
  vector<Point> res{};
  unordered_map<int, bool> visited{};
  Point current(this->start);
  int size = this->walls[current.y].size();
  auto direction = this->direction;
  // std::cout << "start: " << current << std::endl;

  while (
    current.y >= 0 && current.y < this->walls.size() &&
    current.x >= 0 && current.x < this->walls[current.y].size()
    )
  {
    if (this->walls[current.y][current.x])
    {
      current.y -= direction.y;
      current.x -= direction.x;
      direction = rotate(direction);
      // this->print(visited, direction, Point{ current.y, current.x });
    }
    else {
      int id = current.y * size + current.x;
      if (!visited.contains(id)) {
        visited[id] = true;
        res.push_back({ current.y, current.x });
      }
    }

    current.y += direction.y;
    current.x += direction.x;
  }

  return res;
}

void Map::print(unordered_map<int, bool> visited, Point direction, Point current)
{
  int size = this->walls[0].size();
  for (int yy = 0; yy < this->walls.size(); yy++)
  {
    for (int xx = 0; xx < this->walls[yy].size(); xx++)
    {
      int id = yy * size + xx;
      if (current.y == yy && current.x == xx)
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
      else if (this->walls[yy][xx])
      {
        std::cout << '#';
      }
      else if (visited.contains(id))
      {
        std::cout << 'X';
      }
      else {
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}

}
