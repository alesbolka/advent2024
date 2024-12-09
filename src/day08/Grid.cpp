#include <algorithm>
#include <iostream>
#include "./day08.h"
#include "../helpers/Point.h"

using std::map;
using std::string;
using std::vector;

namespace day08
{
using namespace helpers::point;

Grid::Grid(vector<string> lines)
{
  antennas = map<char, vector<Point>>{};
  sizeY = lines.size();
  this->lines = lines;

  for (int yy = 0; yy < lines.size(); yy++)
  {
    sizeX = lines[yy].size();
    for (int xx = 0; xx < lines[yy].size(); xx++)
    {
      char ch = lines[yy][xx];
      if (ch == '.')
      {
        continue;
      }

      antennas[ch].push_back(Point(yy, xx));
    }
  }
};

inline bool inGrid(Point pt, int sizeY, int sizeX)
{
  return pt.y >= 0 && pt.y < sizeY &&
    pt.x >= 0 && pt.x < sizeX;
}

int64_t Grid::findAntinodes()
{
  map<Point, bool> antinodes{};

  for (auto const& pair : antennas)
  {
    for (int ii = 0; ii < pair.second.size(); ii++)
    {
      for (int jj = ii + 1; jj < pair.second.size(); jj++)
      {
        Point diff = pair.second[ii] - pair.second[jj];
        Point new1 = pair.second[ii] + diff;
        Point new2 = pair.second[jj] - diff;
        if (inGrid(new1, sizeY, sizeX))
        {
          antinodes[new1] = true;
        }
        if (inGrid(new2, sizeY, sizeX))
        {
          antinodes[new2] = true;
        }
      }
    }
  }

  return antinodes.size();
}

int64_t Grid::findHarmonicAntinodes()
{
  map<Point, bool> antinodes{};

  for (auto const& pair : antennas)
  {
    for (int ii = 0; ii < pair.second.size(); ii++)
    {
      for (int jj = ii + 1; jj < pair.second.size(); jj++)
      {
        Point diff = pair.second[ii] - pair.second[jj];
        Point newNode = pair.second[ii] + diff;
        antinodes[pair.second[ii]] = true;
        antinodes[pair.second[jj]] = true;

        while (inGrid(newNode, sizeY, sizeX)) {
          antinodes[newNode] = true;
          newNode = newNode + diff;
        }

        newNode = pair.second[jj] - diff;
        while (inGrid(newNode, sizeY, sizeX)) {
          antinodes[newNode] = true;
          newNode = newNode - diff;
        }
      }
    }
  }

  // print(antinodes);

  return antinodes.size();
}

void Grid::print(map<Point, bool> antis)
{
  for (int yy = 0; yy < sizeY; yy++)
  {
    for (int xx = 0; xx < sizeX; xx++)
    {
      Point current{ yy,xx };
      if (lines[yy][xx] != '.') {
        std::cout << lines[yy][xx];
      }
      else if (antis[current])
      {
        std::cout << '#';
      }
      else {
        std::cout << '.';
      }
    }

    std::cout << std::endl;
  }
}

}