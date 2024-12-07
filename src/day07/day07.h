#ifndef DAY_07
#define DAY_07

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../helpers/helpers.h"

namespace day07
{

class Equation
{
public:
  Equation(std::string line)
  {
    auto data = helpers::parseUInts64FromLine(line);
    this->_result = data[0];
    this->numbers = std::vector<uint64_t>(data.begin() + 1, data.end());
  };

  bool solvable();
  bool solvable2();
  const uint64_t result() const { return _result; };

protected:
  int64_t _result;
  std::vector<uint64_t> numbers;
};

inline int64_t task1(std::vector<std::string> lines)
{
  int64_t res = 0;

  for (auto line : lines)
  {
    auto eq = Equation(line);
    auto isOK = eq.solvable();
    if (isOK)
    {
      res += eq.result();
    }
  }

  return res;
}

inline int64_t task2(std::vector<std::string> lines)
{
  int64_t res = 0;

  for (auto line : lines)
  {
    auto eq = Equation(line);
    auto isOK = eq.solvable2();

    if (isOK)
    {
      res += eq.result();
    }
  }

  return res;
}

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