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
  auto numbers = helpers::parseInts64FromLine(line);
  if (numbers.size() != 2)
  {
    throw std::invalid_argument("expected 2 numbers in line: " + line);
  }

  if (_size == 0)
  {
    Xa = numbers[0];
    Ya = numbers[1];
  }
  else if (_size == 1) {
    Xb = numbers[0];
    Yb = numbers[1];
  }
  else {
    TargetX = numbers[0];
    TargetY = numbers[1];
  }

  _size++;
  return _size;
}

uint64_t Machine::bruteForce()
{
  if (_size != 3)
  {
    throw std::invalid_argument("expected 3 sets of parameters to solve this equation");
  }

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
          (TargetX % (pressA * Xa + pressB * Xb)) == 0 &&
          (TargetY % (pressA * Ya + pressB * Yb)) == 0 &&
          TargetX == (pressA * Xa + pressB * Xb) &&
          TargetY == (pressA * Ya + pressB * Yb)
        )
        {
          return pressA * 3 + pressB;
        }
      }
    }
  }

  return 0;
}

uint64_t Machine::equation(uint64_t offset, uint64_t maxPushes)
{
  double Xa = static_cast<double>(this->Xa);
  double Xb = static_cast<double>(this->Xb);
  double Ya = static_cast<double>(this->Ya);
  double Yb = static_cast<double>(this->Yb);
  double TargetX = static_cast<double>(this->TargetX + offset);
  double TargetY = static_cast<double>(this->TargetY + offset);
  /**
   * Started out with this exact logic, but was dumb and was diving ints. Expected task 2 to need this anyway, so I
   * reimplemented it (though still incorrectly apparently)
   * A * Xa + B * Xb = TargetX
   * A * Ya + B * Yb = TargetY
   * B = (TargetY - A * Ya) / Yb
   *
   * A * Xa + Xb * (TargetY - A * Ya) / Yb = TargetX
   * A * (Xa - Xb * Ya / Yb) + Xb * TargetY / Yb = TargetX
   * A = (TargetX - Xb * TargetY / Yb) / (Xa - Xb * Ya / Yb)
   */

  if (Yb == 0 || (Xa - Xb * Ya / Yb) == 0) {
    return 0;
  }

  // I'm honestly not sure why it had to be rounded - I expected that any proper solution would end up with an integer
  // Assuming that it's an error with how doubles are represented in binary, quite possible I'm just dumb
  uint64_t A = std::round((TargetX - Xb * TargetY / Yb) / (Xa - Xb * Ya / Yb));
  uint64_t B = std::round((TargetY - A * Ya) / Yb);

  uint64_t sumX = A * this->Xa + B * this->Xb;
  uint64_t sumY = A * this->Ya + B * this->Yb;
  if (
    sumX == (this->TargetX + offset) && sumY == (this->TargetY + offset) &&
    (maxPushes == 0 || maxPushes >= A && maxPushes >= B)
  )
  {
    return A * 3 + B;
  }

  return 0;
}

}