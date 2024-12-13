#include "./day10.h"

namespace day10
{

uint64_t task1(std::vector<std::string> lines)
{
  Map map(lines);

  return map.trailScore();
}

uint64_t task2(std::vector<std::string> lines)
{
  Map map(lines);

  return map.trailScoreV2();
}

}