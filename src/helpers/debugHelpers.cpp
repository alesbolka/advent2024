#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <regex>
#include "./helpers.h"

namespace helpers {

void printIntVector(std::vector<int> vec)
{
  std::cout << "(";
  for (int ii = 0; ii < vec.size(); ii++)
  {
    std::cout << vec[ii] << (ii == (vec.size() - 1) ? "" : ", ");
  }
  std::cout << ")";
}

}