#ifndef DAY_01
#define DAY_01

#include <vector>
#include <string>

namespace day01 {

int64_t task1(std::vector<std::string> input);
int64_t task2(std::vector<std::string> input);

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