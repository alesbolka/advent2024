#include "./day07.h"
#include "../helpers/helpers.h"

using std::vector;
using std::string;
using std::map;

namespace day07
{

bool subEquation(uint64_t working, vector<uint64_t>* numbers, int index)
{
  uint64_t num = (*numbers)[index];

  if (index == 1)
  {
    uint64_t tmp = (*numbers)[0] + (*numbers)[1];
    uint64_t tmp2 = (*numbers)[0] * (*numbers)[1];

    return tmp == working || tmp2 == working;
  }

  if (index != 0 && (working % num) == 0)
  {
    bool divRes = subEquation(working / num, numbers, index - 1);
    if (divRes)
    {
      return true;
    }
  }

  return num <= working && subEquation(working - num, numbers, index - 1);
}

bool Equation::solvable()
{
  return subEquation(this->_result, &numbers, numbers.size() - 1);
}

inline uint64_t conc_numbers(uint64_t first, uint64_t second)
{
  auto power = std::floor(std::log10(second)) + 1;
  return first * std::pow(10, power) + second;
}

bool subEquation2(uint64_t finalResult, vector<uint64_t>* numbers, int index, uint64_t carry)
{
  auto num = (*numbers)[index];
  if (index == (*numbers).size() - 1)
  {
    return (num + carry) == finalResult || (num * carry) == finalResult || conc_numbers(carry, num) == finalResult;
  }

  return subEquation2(finalResult, numbers, index + 1, num + carry) ||
    subEquation2(finalResult, numbers, index + 1, num * carry) ||
    subEquation2(finalResult, numbers, index + 1, conc_numbers(carry, num));
}

bool Equation::solvable2()
{
  return subEquation2(_result, &numbers, 1, numbers[0]);
}

}