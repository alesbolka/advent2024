#include <iostream>
#include <string>
#include "helpers/helpers.h"
#include "./day01/day01.h"
#include "./day02/day02.h"
#include "./day03/day03.h"

int main(int argc, char** argv)
{
  int day = 3;
  int task = 2;
  int64_t result = -1;

  char path[64];

  std::string name = "sample";

  sprintf(path, "./inputs/day%02d/%s.txt", day, name.c_str());

  auto data = helpers::readFileLines(path);

  switch (day)
  {
  case 1:
    result = day01::executor(task, data);
    break;
  case 2:
    result = day02::executor(task, data);
    break;
  case 3:
    result = day03::executor(task, data);
    break;
  case 4:
    std::cout << "lost code during botched rebase, might re-implement later" << std::endl;
    break;
  case 5:
    std::cout << "lost code during botched rebase, might re-implement later" << std::endl;
    break;
  default:
    std::cout << "Invalid day requested" << std::endl;
    return 1;
  }

  std::cout << "Day " << day << " task " << task << std::endl << "result: " << result << std::endl;
}