#include "./day14.h"

namespace day14
{
using std::vector;
using std::string;

Grid::Grid(vector<string> lines, int gridY, int gridX)
{
  sizeY = gridY;
  sizeX = gridX;

  for (auto line : lines)
  {
    auto numbers = helpers::parseIntsFromLine(line);
    guards.push_back(Guard(Point{ numbers[1], numbers[0] }, Point{ numbers[3], numbers[2] }));
  }
}


uint64_t Grid::simulateMovement(int steps)
{
  uint64_t quadCount[4] = { 0,0,0,0 };
  int midY = sizeY / 2;
  int midX = sizeX / 2;

  std::map<Point, int>dist{};

  for (auto guard : guards)
  {
    if (guard.pos0.y >= sizeY || guard.pos0.x >= sizeX) {
      continue;
    }
    Point newPos(guard.pos0);

    newPos += guard.dir * steps;
    newPos.y = (newPos.y + sizeY * steps) % sizeY;
    newPos.x = (newPos.x + sizeX * steps) % sizeX;
    dist[newPos] += 1;

    if (newPos.y < midY)
    {
      if (newPos.x < midX)
      {
        quadCount[0]++;
      }
      else if (newPos.x > midX) {
        quadCount[1]++;
      }
    }
    else if (newPos.y > midY) {
      if (newPos.x < midX)
      {
        quadCount[2]++;
      }
      else if (newPos.x > midX) {
        quadCount[3]++;
      }
    }
  }

  return quadCount[0] * quadCount[1] * quadCount[2] * quadCount[3];
}

uint64_t Grid::stepsToTree()
{
  vector<Point> positions{};
  vector<string> output{};

  for (int ii = 0; ii < guards.size(); ii++)
  {
    positions.push_back(guards[ii].pos0);
  }

  uint64_t steps = 0;
  uint64_t max = steps - 1;

  // Stupid bruteforce go!
  while (steps < max)
  {
    steps++;
    output = vector<string>(sizeY, string(sizeX, '.'));

    for (int ii = 0; ii < guards.size(); ii++)
    {
      positions[ii] += guards[ii].dir;
      positions[ii].y = (positions[ii].y + sizeY) % sizeY;
      positions[ii].x = (positions[ii].x + sizeX) % sizeX;
      output[positions[ii].y][positions[ii].x] = '#';
    }

    for (auto line : output)
    {
      if (line.find("############") != string::npos)
      {
        for (auto line : output)
        {
          std::cout << line << std::endl;
        }
        return steps;
      }
    }
  }

  return -1;
}

}