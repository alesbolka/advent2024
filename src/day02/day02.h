#ifndef DAY_02
#define DAY_02
#include "../inputs/day02.h"

namespace day02 {

int64_t task1(std::string input);
int64_t task2(std::string input);

inline int64_t executor(int task)
{
  auto input = inputs::day02::input;
  // auto input = std::string("84 82 83 84 85 88 90");

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
