#include "./day10.h"

namespace day10
{

int64_t task1(std::vector<std::string> lines)
{
  Map map(lines);

  return map.trailScore();
}

int64_t task2(std::vector<std::string> lines)
{
  Map map(lines);

  return map.trailScoreV2();
}

}