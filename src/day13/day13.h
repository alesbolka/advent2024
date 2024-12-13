#ifndef DAY_13
#define DAY_13

#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <vector>
#include "../helpers/helpers.h"

namespace day13
{

class Machine
{
public:
  Machine() {
    _size = 0;
    Xa = 0;
    Xb = 0;
    Ya = 0;
    Yb = 0;
    TargetX = 0;
    TargetY = 0;
  };

  uint64_t bruteForce();
  uint64_t equation(uint64_t offset = 0, uint64_t maxPushes = 0);
  int addParams(std::string line);

  int size() { return _size; };
protected:
  uint64_t Xa;
  uint64_t Xb;
  uint64_t Ya;
  uint64_t Yb;
  uint64_t TargetX;
  uint64_t TargetY;
  uint64_t _size;
};

inline uint64_t executor(int task, std::vector<std::string> input)
{
  std::vector<Machine> machines{};
  std::vector<uint64_t> scores{};
  Machine mach{};

  for (auto line : input)
  {
    if (line == "") {
      continue;
    }

    if (mach.addParams(line) == 3)
    {
      machines.push_back(mach);
      if (task == 1)
      {
        // scores.push_back(mach.bruteForce());
        scores.push_back(mach.equation(0, 100));
      }
      else {
        scores.push_back(mach.equation(10000000000000));
      }
      mach = Machine();
    }
  }

  std::sort(scores.begin(), scores.end());
  uint64_t res = 0;
  for (uint64_t score : scores)
  {
    res += score;
  }

  return res;
};
}

#endif
