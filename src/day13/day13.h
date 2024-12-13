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
    x0 = 0;
    x1 = 0;
    y0 = 0;
    y1 = 0;
    cx = 0;
    cy = 0;
  };

  int bruteForce();
  int addParams(std::string line);

  int size() { return _size; };
protected:
  int x0;
  int x1;
  int y0;
  int y1;
  int cx;
  int cy;
  int _size;
};

inline int64_t executor(int task, std::vector<std::string> input)
{
  std::vector<Machine> machines{};
  std::vector<int> scores{};
  Machine mach{};

  for (auto line : input)
  {
    // std::cout << line << std::endl;
    if (line == "") {
      continue;
    }

    if (mach.addParams(line) == 3)
    {
      machines.push_back(mach);
      scores.push_back(mach.bruteForce());
      mach = Machine();
    }
  }

  if (task == 1) {
    std::sort(scores.begin(), scores.end());
    int64_t res = 0;
    for (int score : scores)
    {
      if (score < 0)
      {
        continue;
      }
      res += score;
    }

    return res;
  }

  if (task == 2) {
    return -1;
  }

  return -1;
};
}

#endif
