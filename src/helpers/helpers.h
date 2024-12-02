#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <regex>

namespace helpers
{

std::vector<std::string> splitString(const std::string& str, char separator = '\n')
{
  std::vector<std::string> result = std::vector<std::string>{};
  auto stream = std::stringstream{ str };

  for (std::string line; std::getline(stream, line, separator);) {
    result.push_back(line);
  }

  return result;
}

/**
 * This is a horribly inefficient helper, but it's somewhat magicky and strips all integers from a string into a vector
 */
std::vector<int> parseIntsFromLine(const std::string& str)
{
  std::vector<int> result = {};

  std::regex number_regex("(\\d+)");
  auto it_start = std::sregex_iterator(str.begin(), str.end(), number_regex);
  auto it_end = std::sregex_iterator();

  for (std::sregex_iterator ii = it_start; ii != it_end; ++ii) {
    std::string match_str = (*ii).str();

    int number = strtol(match_str.c_str(), NULL, 10);
    if (std::to_string(number) != match_str)
    {
      throw std::invalid_argument("Failed parsing number (" + match_str + ") from " + str);
    }

    result.push_back(number);
  }
  return result;
}

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
