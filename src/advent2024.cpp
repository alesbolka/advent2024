#include <iostream>
#include "helpers/helpers.h"
#include "./day01/day01.h"
#include "./day02/day02.h"
#include "./day03/day03.h"

int main(int argc, char** argv)
{
  int day = 3;
  int task = 2;
  int64_t result = day01::executor(task);

  switch (day)
  {
  case 1:
    result = day01::executor(task);
    break;
  case 2:
    result = day02::executor(task);
    break;
  case 3:
    result = day03::executor(task);
    break;
  default:
    std::cout << "Invalid day requested" << std::endl;
    return 1;
  }

  std::cout << "Day " << day << " task " << task << std::endl
    << "result: " << result << std::endl;
}