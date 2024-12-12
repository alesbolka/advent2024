#include "./day12.h"

namespace day12
{

using std::vector;
using std::queue;
using std::map;
using std::string;
using helpers::point::Point;
using helpers::point::directions::UP;
using helpers::point::directions::DOWN;
using helpers::point::directions::LEFT;
using helpers::point::directions::RIGHT;

const Point directions[4] = {
  UP,
  DOWN,
  LEFT,
  RIGHT,
};

Region::Region(Point start, const vector<string>& lines)
{
  plots = map<Point, char>{};

  queue<Point> toProcess{ };
  toProcess.push(start);
  plant = lines[start.y][start.x];

  while (!toProcess.empty())
  {
    Point node = toProcess.front();
    toProcess.pop();
    plots[node] = 4;
    _nodes.push_back(node);

    for (auto dir : directions)
    {
      Point neighbour = dir + node;
      if (
        neighbour.y < 0 || neighbour.y >= lines.size() ||
        neighbour.x < 0 || neighbour.x >= lines[neighbour.y].size()
      )
      {
        continue;
      }

      if (lines[neighbour.y][neighbour.x] == plant)
      {
        plots[node]--;
        if (!plots.contains(neighbour))
        {
          toProcess.push(neighbour);
          plots[neighbour] = 4;
        }
      }
    }
  }
};

int64_t Region::fencePrice()
{
  int64_t res = 0;
  for (auto plot : plots)
  {
    res += plot.second;
  }
  res *= plots.size();

  return res;
}

vector<Point> Region::runEdge(Point startPlot, Point edgeSide)
{
  Point edgeStart(startPlot);
  Point edgeEnd(startPlot);

  Point edgeDirection = edgeSide.rotate();
  while (plots.contains(edgeEnd + edgeDirection) && !plots.contains(edgeEnd + edgeDirection + edgeSide))
  {
    edgeEnd += edgeDirection;
  }

  while (plots.contains(edgeStart - edgeDirection) && !plots.contains(edgeStart - edgeDirection + edgeSide))
  {
    edgeStart -= edgeDirection;
  }

  return vector<Point>{edgeStart, edgeEnd};
}

int64_t Region::discountedPrice()
{
  int64_t res = 0;
  map<Point, map<Point, bool>> alreadyChecked{};

  for (auto plot : plots)
  {
    for (auto edgeSide : directions) {
      if (
        !plots.contains(plot.first + edgeSide) &&
        !alreadyChecked[edgeSide][plot.first]
      )
      {
        auto edgePoints = runEdge(plot.first, edgeSide);
        auto edgeDir = edgeSide.rotate();
        auto edgeNode = edgePoints[0];
        alreadyChecked[edgeSide][edgeNode] = true;
        alreadyChecked[edgeSide][edgePoints[1]] = true;
        res++;

        while (edgeNode != edgePoints[1])
        {
          alreadyChecked[edgeSide][edgeNode] = true;
          edgeNode += edgeDir;
        }
      }
    }
  }

  res *= plots.size();
  return res;
}

}