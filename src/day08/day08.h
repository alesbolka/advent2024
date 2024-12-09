#ifndef DAY_08
#define DAY_08

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../helpers/helpers.h"
#include "../helpers/Point.h"

namespace day08
{

using helpers::point::Point;

class Grid
{
public:
  Grid(std::vector<std::string> lines);
  int64_t findAntinodes();
  int64_t findHarmonicAntinodes();
protected:
  std::map<char, std::vector<Point>> antennas;
  std::vector<std::string> lines;
  int sizeY;
  int sizeX;

  void print(std::map<Point, bool> antinodes);
};

inline int64_t task1(std::vector<std::string> lines)
{
  Grid map = Grid(lines);

  return map.findAntinodes();
}

inline int64_t task2(std::vector<std::string> lines)
{
  Grid map = Grid(lines);

  return map.findHarmonicAntinodes();
}

inline int64_t executor(int task, std::vector<std::string> input)
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