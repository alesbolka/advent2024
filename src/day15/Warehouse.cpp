#include "./day15.h"

namespace day15
{
using std::vector;
using std::string;
using helpers::point::Point;
using helpers::point::directions::UP;
using helpers::point::directions::RIGHT;
using helpers::point::directions::DOWN;
using helpers::point::directions::LEFT;

Warehouse::Warehouse(vector<string> lines)
{
  bool parsingGrid = true;
  sizeY = 0;
  for (auto line : lines) {
    if (line == "")
    {
      parsingGrid = false;
      continue;
    }

    if (parsingGrid)
    {
      grid.push_back(line);
      sizeX = line.size();
      largeGrid.push_back(string(sizeX * 2, '.'));

      for (int xx = 0; xx < sizeX; xx++)
      {
        if (line[xx] == '#')
        {
          largeGrid[sizeY][2 * xx] = '#';
          largeGrid[sizeY][2 * xx + 1] = '#';
        }
        else if (line[xx] == 'O')
        {
          largeGrid[sizeY][2 * xx] = '[';
          largeGrid[sizeY][2 * xx + 1] = ']';
        }
        else if (line[xx] == '@')
        {
          robot = Point(sizeY, xx);
          grid[sizeY][xx] = '.';
        }
      }
      sizeY++;
    }
    else {
      instructions.push_back(line);
    }
  }
}
void Warehouse::print(bool large)
{
  if (!large) {
    for (int yy = 0; yy < sizeY; yy++)
    {
      for (int xx = 0; xx < sizeX; xx++)
      {
        if (robot.y == yy && robot.x == xx)
        {
          std::cout << '@';
        }
        else {
          std::cout << grid[yy][xx];
        }
      }
      std::cout << std::endl;
    }
  }

  for (int yy = 0; yy < sizeY; yy++)
  {
    for (int xx = 0; xx < (sizeX * 2); xx++)
    {
      if (robot.y == yy && robot.x == xx)
      {
        std::cout << '@';
      }
      else {
        std::cout << largeGrid[yy][xx];
      }
    }
    std::cout << std::endl;
  }
}

void Warehouse::executeCommands()
{
  int ii = 0;
  for (string line : instructions)
  {
    for (char command : line)
    {
      ii++;
      step(command);
    }
  }
}

void Warehouse::step(char command)
{
  std::map<char, Point> directions{
    {'^', helpers::point::directions::UP},
    {'>', helpers::point::directions::RIGHT},
    {'v', helpers::point::directions::DOWN},
    {'<', helpers::point::directions::LEFT},
  };

  if (!directions.contains(command))
  {
    throw std::invalid_argument("Invalid command " + std::to_string(command));
  }

  Point dir = directions[command];
  Point nextRobot = robot + dir;
  vector<Point> boxes{};

  Point next(nextRobot);

  while (grid[next.y][next.x] == 'O')
  {
    next += dir;
  }

  if (grid[next.y][next.x] == '#')
  {
    return;
  }

  grid[next.y][next.x] = 'O';
  grid[nextRobot.y][nextRobot.x] = '.';
  robot = nextRobot;
}

uint64_t Warehouse::boxScore()
{
  uint64_t res = 0;
  for (int yy = 0; yy < sizeY; yy++)
  {
    for (int xx = 0; xx < sizeX; xx++)
    {
      if (grid[yy][xx] == 'O')
      {
        res += 100 * yy + xx;
      }
    }
  }
  return res;
}

uint64_t Warehouse::executeCommandsLarge()
{
  uint64_t res = 0;
  robot = Point(robot.y, robot.x * 2); // adjust for larger size

  for (string line : instructions)
  {
    for (char command : line)
    {
      stepLarge(command);
    }
  }

  for (int yy = 0; yy < largeGrid.size(); yy++)
  {
    for (int xx = 0; xx < largeGrid[yy].size(); xx++)
    {
      if (largeGrid[yy][xx] != '[')
      {
        continue;
      }

      res += yy * 100 + xx;
      // conflicting instructions made me overengineer it
      // res += std::min(yy, sizeY - yy - 1) * 100 + std::min(xx + 1, sizeX - xx);
    }
  }

  return res;
}

void Warehouse::stepLarge(char command)
{
  string box = "[]";
  std::map<char, Point> directions{
    {'^', UP},
    {'>', RIGHT},
    {'v', DOWN},
    {'<', LEFT},
  };

  if (!directions.contains(command))
  {
    throw std::invalid_argument("Invalid command " + std::to_string(command));
  }

  Point dir = directions[command];
  Point nextRobot = robot + dir;

  if (dir == LEFT || dir == RIGHT)
  {
    Point next(nextRobot);
    int boxCount = 0;


    while (largeGrid[next.y][next.x] == '[' || largeGrid[next.y][next.x] == ']')
    {
      boxCount += largeGrid[next.y][next.x] == '[';
      next += dir;
    }
    if (largeGrid[next.y][next.x] == '#')
    {
      return;
    }

    robot = Point(nextRobot);
    largeGrid[robot.y][robot.x] = '.';

    while (nextRobot != next)
    {
      if (dir == RIGHT)
      {
        nextRobot.x += 2;
        largeGrid[robot.y][nextRobot.x - 1] = '[';
        largeGrid[robot.y][nextRobot.x] = ']';
      }
      else {
        nextRobot.x -= 2;
        largeGrid[robot.y][nextRobot.x] = '[';
        largeGrid[robot.y][nextRobot.x + 1] = ']';
      }
    }
    return;
  }

  int nextY = robot.y + dir.y;
  bool keepGoing = true;
  vector<int> POIs{ robot.x };
  vector<Point> boxStarts{};

  while (POIs.size() > 0)
  {
    vector<int> newPOIs{ };
    for (int poi : POIs)
    {
      if (largeGrid[nextY][poi] == '#')
      {
        return;
      }
      else if (largeGrid[nextY][poi] == '.')
      {
        // already checking this out
        continue;
      }
      else if (largeGrid[nextY][poi] == '[')
      {
        newPOIs.push_back(poi);
        newPOIs.push_back(poi + 1);
        boxStarts.push_back(Point(nextY, poi));
      }
      // don't re-discover the same box
      else if (largeGrid[nextY][poi] == ']' && std::find(newPOIs.begin(), newPOIs.end(), poi) == newPOIs.end())
      {
        newPOIs.push_back(poi - 1);
        newPOIs.push_back(poi);
        boxStarts.push_back(Point(nextY, poi - 1));
      }
    }

    POIs = newPOIs;
    nextY += dir.y;
  }

  for (auto boxStart : boxStarts)
  {
    largeGrid[boxStart.y][boxStart.x] = '.';
    largeGrid[boxStart.y][boxStart.x + 1] = '.';
  }

  for (auto boxStart : boxStarts)
  {
    largeGrid[boxStart.y + dir.y][boxStart.x] = '[';
    largeGrid[boxStart.y + dir.y][boxStart.x + 1] = ']';
  }

  robot += dir;
}

}