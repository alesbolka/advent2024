#include <iostream>
#include <stdexcept>
#include "./day13.h"

namespace day13
{

int Machine::addParams(std::string line)
{
  if (_size > 2) {
    throw std::invalid_argument("attempted to add a 4th line to equation set: " + line);
  }
  auto numbers = helpers::parseIntsFromLine(line);
  if (numbers.size() != 2)
  {
    throw std::invalid_argument("expected 2 numbers in line: " + line);
  }

  if (_size == 0)
  {
    x0 = numbers[0];
    y0 = numbers[1];
  }
  else if (_size == 1) {
    x1 = numbers[0];
    y1 = numbers[1];
  }
  else {
    cx = numbers[0];
    cy = numbers[1];
  }

  _size++;
  return _size;
}

// int estimateTokenCost(int x0, int y0, int)

int Machine::bruteForce()
{
  if (_size != 3)
  {
    throw std::invalid_argument("expected 3 sets of parameters to solve this equation");
  }

  // std::cout << "x0: " << x0 << ", x1: " << x1 << ", cx: " << cx << std::endl;

  for (int startB = 0; startB <= 100; startB += 3)
  {
    for (int pressA = 0; pressA <= 100; pressA++)
    {
      for (int pressB = startB; pressB < (startB + 3); pressB++)
      {
        if (pressB > 100 || pressA == 0 && pressB == 0)
        {
          continue;
        }



        if (
          (cx % (pressA * x0 + pressB * x1)) == 0 &&
          (cy % (pressA * y0 + pressB * y1)) == 0 &&
          cx == (pressA * x0 + pressB * x1) &&
          cy == (pressA * y0 + pressB * y1)
        )
        {
          return pressA * 3 + pressB;
        }
      }
    }
  }


  return -1;
}

}