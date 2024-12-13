#include <iostream>
#include <unordered_map>
#include "./day06.h"

namespace day06
{


void Map::print(std::unordered_map<uint64_t, bool> visited, Point direction, Point current, Point* tmpBlocker)
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
      else if (tmpBlocker != nullptr && (*tmpBlocker).x == xx && (*tmpBlocker).y == yy)
      {
        std::cout << 'O';
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
  std::cout << std::endl;
}

}