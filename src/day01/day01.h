#ifndef DAY_01
#define DAY_01
#include "../inputs/day01.h"

namespace day01 {

int64_t task1(std::string input);
int64_t task2(std::string input);

inline int64_t executor(int task)
{
  auto input = inputs::day01::input;

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
