#include <iostream>
#include "day01/day01.h"

int main(int argc, char** argv)
{
  int day = 1;
  int task = 2;
  int64_t result = day01::executor(task);

  std::cout << "Day " << day << " task " << task << std::endl
    << "result: " << result << std::endl;
}