#ifndef DAY_03
#define DAY_03

#include <vector>
#include <string>

namespace day03 {

uint64_t task1(std::string input);
uint64_t task2(std::string input);

inline uint64_t executor(int task, std::vector<std::string> input)
{

  if (task == 1) {
    return task1(input[0]);
  }

  if (task == 2) {
    return task2(input[0]);
  }

  return -1;
};

}

#endif
