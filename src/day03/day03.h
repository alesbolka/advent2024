#ifndef DAY_03
#define DAY_03
#include "../inputs/day03.h"

namespace day03 {

int64_t task1(std::string input);
int64_t task2(std::string input);

inline int64_t executor(int task)
{
  auto input = inputs::day03::input;

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
