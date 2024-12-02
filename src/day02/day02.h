#ifndef DAY_02
#define DAY_02


#include <vector>
#include <string>

namespace day02 {

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
