#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <regex>
#include "./helpers.h"

namespace helpers {

std::vector<std::string> readFileLines(const std::string path)
{
  std::vector<std::string> result{};
  std::string line;

  std::ifstream fileHandle(path.c_str());

  if (!fileHandle.is_open())
  {
    throw std::invalid_argument("could not open path: " + path);
  }

  while (std::getline(fileHandle, line))
  {
    result.push_back(line);
  }

  if (result[result.size() - 1] == "")
  {
    result.pop_back();
  }

  return result;
}

std::vector<std::string> splitString(const std::string& str, char separator)
{
  std::vector<std::string> result = std::vector<std::string>{};
  auto stream = std::stringstream{ str };

  for (std::string line; std::getline(stream, line, separator);) {
    result.push_back(line);
  }

  return result;
}

std::vector<int> parseIntsFromLine(const std::string& str)
{
  std::vector<int> result = {};

  std::regex number_regex("(\\-?\\d+)");
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

std::vector<u_int64_t> parseUInts64FromLine(const std::string& str)
{
  std::vector<u_int64_t> result = {};

  std::regex number_regex("(\\-?\\d+)");
  auto it_start = std::sregex_iterator(str.begin(), str.end(), number_regex);
  auto it_end = std::sregex_iterator();

  for (std::sregex_iterator ii = it_start; ii != it_end; ++ii) {
    std::string match_str = (*ii).str();

    uint64_t number = strtoull(match_str.c_str(), NULL, 10);
    if (std::to_string(number) != match_str)
    {
      throw std::invalid_argument("Failed parsing number (" + match_str + ") from " + str);
    }

    result.push_back(number);
  }
  return result;
}

std::vector<uint64_t> parseInts64FromLine(const std::string& str)
{
  std::vector<uint64_t> result = {};

  std::regex number_regex("(\\-?\\d+)");
  auto it_start = std::sregex_iterator(str.begin(), str.end(), number_regex);
  auto it_end = std::sregex_iterator();

  for (std::sregex_iterator ii = it_start; ii != it_end; ++ii) {
    std::string match_str = (*ii).str();

    uint64_t number = strtoll(match_str.c_str(), NULL, 10);
    if (std::to_string(number) != match_str)
    {
      throw std::invalid_argument("Failed parsing number (" + match_str + ") from " + str);
    }

    result.push_back(number);
  }
  return result;
}

}