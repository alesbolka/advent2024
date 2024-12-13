#include "./day11.h"
#include "../helpers/helpers.h"

#include <iostream>

namespace day11
{

using std::vector;
using std::map;

map<uint64_t, uint64_t> blink(map<uint64_t, uint64_t>* stones, int blinkNumber)
{
  map<uint64_t, uint64_t> result(*stones);

  for (int ii = 0; ii < blinkNumber; ii++)
  {
    // std::cout << "blink " << ii << std::endl;
    map<uint64_t, uint64_t> newStones{};
    for (auto stone : result)
    {
      // std::cout << "stone value: " << stone.first << std::endl;
      int digits = std::log10(stone.first) + 1;
      if (stone.first == 0)
      {
        newStones[1] += stone.second;
      }
      else if (digits % 2 == 0) {
        int divider = std::pow(10, digits / 2);
        // std::cout << "\tdividing by " << divider << ", left: " << stone.first / divider << ", right: " << stone.first % divider << std::endl;
        newStones[stone.first / divider] += stone.second;
        newStones[stone.first % divider] += stone.second;
      }
      else {
        newStones[stone.first * 2024] += result[stone.first];
        // std::cout << "\tmultiplying by 2024: " << stone.first * 2024 << std::endl;
      }
    }

    result = newStones;
  }

  return result;
}

uint64_t task1(std::vector<std::string> lines)
{
  map<uint64_t, uint64_t> stoneMap{};
  for (int stoneVal : helpers::parseUInts64FromLine(lines[0])) {
    stoneMap[stoneVal] += 1;
  }

  uint64_t result = 0;
  for (auto stone : blink(&stoneMap, 25))
  {
    result += stone.second;
  }

  return result;
}

uint64_t task2(std::vector<std::string> lines)
{
  map<uint64_t, uint64_t> stoneMap{};
  for (int stoneVal : helpers::parseUInts64FromLine(lines[0])) {
    stoneMap[stoneVal] += 1;
  }

  uint64_t result = 0;
  for (auto stone : blink(&stoneMap, 75))
  {
    result += stone.second;
  }

  return result;
}

}