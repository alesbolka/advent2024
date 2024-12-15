#ifndef DAY_15
#define DAY_15

#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include "../helpers/helpers.h"
#include "../helpers/Point.h"

namespace day15
{

using helpers::point::Point;

class Warehouse
{
public:
  Warehouse(std::vector<std::string> lines);
  uint64_t boxScore();
  void executeCommands();
  uint64_t executeCommandsLarge();
protected:
  int sizeY;
  int sizeX;
  std::vector<std::string> grid;
  std::vector<std::string> largeGrid;
  std::vector<std::string> instructions;
  Point robot;

  void step(char command);
  void stepLarge(char command);
  void print(bool large = false);
};

inline uint64_t executor(int task, std::vector<std::string> input)
{
  Warehouse wh(input);
  if (task == 1)
  {
    wh.executeCommands();
    return wh.boxScore();
  }

  return wh.executeCommandsLarge();
};
}

#endif
