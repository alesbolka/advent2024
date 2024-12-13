#include <iostream>
#include <string>
#include "helpers/helpers.h"
#include "./day01/day01.h"
#include "./day02/day02.h"
#include "./day03/day03.h"
#include "./day06/day06.h"
#include "./day07/day07.h"
#include "./day08/day08.h"
#include "./day09/day09.h"
#include "./day10/day10.h"
#include "./day11/day11.h"
#include "./day12/day12.h"
#include "./day13/day13.h"

int main(int argc, char** argv)
{
  int day = 13;
  int task = 2;
  uint64_t result = -1;

  char path[64];

  std::string name = "input";

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
  case 6:
    result = day06::executor(task, data);
    break;
  case 7:
    result = day07::executor(task, data);
    break;
  case 8:
    result = day08::executor(task, data);
    break;
  case 9:
    result = day09::executor(task, data);
    break;
  case 10:
    result = day10::executor(task, data);
    break;
  case 11:
    result = day11::executor(task, data);
    break;
  case 12:
    result = day12::executor(task, data);
    break;
  case 13:
    result = day13::executor(task, data);
    break;
  default:
    std::cout << "Invalid day requested" << std::endl;
    return 1;
  }

  std::cout << "Day " << day << " task " << task << std::endl << "result: " << result << std::endl;
}