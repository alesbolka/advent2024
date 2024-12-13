#ifndef DAY_11
#define DAY_11

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace day11
{

uint64_t task1(std::vector<std::string> lines);
uint64_t task2(std::vector<std::string> lines);

inline uint64_t executor(int task, std::vector<std::string> input)
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
