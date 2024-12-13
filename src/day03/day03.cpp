#include <regex>
#include <string>
#include <vector>
#include "../helpers/helpers.h"
#include "./day03.h"

using std::vector;
using std::string;

namespace day03
{

uint64_t task1(std::string input)
{
  uint64_t result = 0;
  std::regex matcher("mul\\((\\d+),(\\d+)\\)");
  auto it_start = std::sregex_iterator(input.begin(), input.end(), matcher);
  auto it_end = std::sregex_iterator();

  for (std::sregex_iterator ii = it_start; ii != it_end; ++ii) {
    std::string subString = (*ii).str();

    auto numbers = helpers::parseIntsFromLine(subString);

    if (numbers.size() != 2) {
      throw std::invalid_argument("Failed parsing numbers from: " + subString);
    }

    result += numbers[0] * numbers[1];
  }
  return result;
}

uint64_t task2(std::string input)
{
  uint64_t result = 0;
  bool enabled = true;
  bool inMul = false;

  for (int ii = 0; ii < input.size(); ii++)
  {
    auto subString = input.substr(ii, 7);
    if (!enabled) {
      enabled = subString.find("do()") != std::string::npos;
    }
    else if (subString == "don't()") {
      enabled = false;
    }
    else if (subString.rfind("mul(", 0) == 0) {
      inMul = true;
      ii += 5;

      for (int jj = 0; jj < (input.size() - ii); jj++)
      {
        char ch = input[jj + ii];
        if (ch >= '0' && ch <= '9' || ch == ',') {
          continue;
        }
        else if (ch == ')') {
          string numString = input.substr(ii - 1, jj + 1);

          auto numbers = helpers::parseIntsFromLine(numString);
          if (numbers.size() != 2) {
            throw std::invalid_argument("Failed parsing numbers from: " + numString);
          }
          result += numbers[0] * numbers[1];
          ii += jj;
          break;
        }
        else {
          // std::cout << "wrong character: \"" << ch << "\"" << std::endl;
          ii += jj;
          break;
        }
      }
      inMul = false;
    }

  }
  return result;
}

}
