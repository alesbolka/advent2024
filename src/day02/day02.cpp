#include <vector>
#include <string>
#include "../helpers/helpers.h"

using std::vector;
using std::string;

namespace day02
{

bool isReportSafe(vector<int> levels, bool semiSafe = false)
{
  int diff = 0;
  for (int ii = 1; ii < levels.size(); ii++) {
    int levelDiff = levels[ii - 1] - levels[ii];
    if (
      levelDiff < -3 || levelDiff > 3 || levelDiff == 0 ||
      levelDiff > 0 && diff < 0 ||
      levelDiff < 0 && diff > 0
      )
    {
      if (semiSafe)
      {
        /**
         * If the first report is "wrong", the level might get flagged as incorrect on the third report. So start by
         * n-2 to avoid errors (it affects the initial "direction" of increasing / decreasing numbers that might get set
         * incorrectly)
         */
        for (int jj = (ii < 3 ? ii - 2 : ii - 1); jj <= ii; jj++) {
          if (jj < 0) {
            continue;
          }
          // simply remove 1 element from the vector and try again
          vector<int> subVector = vector<int>(levels);
          subVector.erase(subVector.begin() + jj);
          if (isReportSafe(subVector, false)) {
            return true;
          }
        }
      }
      return false;
    }

    diff = levelDiff;
  }

  return true;
}

uint64_t task1(vector<string> input)
{
  uint64_t res = 0;
  for (auto line : input) {
    bool isSafe = isReportSafe(helpers::parseIntsFromLine(line));
    if (isSafe) {
      res++;
    }
  }

  return res;
}

uint64_t task2(vector<string> input)
{
  uint64_t res = 0;
  for (auto line : input) {
    bool isSafe = isReportSafe(helpers::parseIntsFromLine(line), true);
    if (isSafe) {
      res++;
    }
  }

  return res;
}
}
