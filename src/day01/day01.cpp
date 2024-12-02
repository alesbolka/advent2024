#include <algorithm>
#include <stdexcept>
#include <vector>
#include "day01.h"
#include "../helpers/helpers.h"

using std::vector;

namespace day01
{

inline bool comp_asc(int xx, int yy) { return xx < yy; }

struct parsedInput {
  vector<int> left;
  vector<int> right;
};

parsedInput parseInput(vector<std::string> lines) {
  parsedInput res{
    left: vector<int>{},
    right : vector<int>{},
  };

  for (const std::string& line : lines)
  {
    std::vector<int> numbers = helpers::parseIntsFromLine(line);
    if (numbers.size() != 2)
    {
      throw std::invalid_argument("Failed constructing result for line: " + line);
    }
    res.left.push_back(numbers[0]);
    res.right.push_back(numbers[1]);
  }

  return res;
}

int64_t task1(vector<std::string> lines)
{
  parsedInput data = parseInput(lines);

  std::sort(data.left.begin(), data.left.end(), comp_asc);
  std::sort(data.right.begin(), data.right.end(), comp_asc);

  int64_t result = 0;

  for (int ii = 0; ii < data.left.size(); ii++)
  {
    int dist = data.right[ii] - data.left[ii];
    result += dist < 0 ? 0 - dist : dist;
  }

  return result;
}

int64_t task2(vector<std::string> lines) {
  parsedInput data = parseInput(lines);
  int64_t res = 0;

  for (int ii = 0; ii < data.left.size(); ii++) {
    int num = data.left[ii];
    res += num * std::count(data.right.begin(), data.right.end(), num);
  }

  return res;
}

}
