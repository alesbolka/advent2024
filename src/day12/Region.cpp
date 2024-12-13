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

uint64_t Region::fencePrice()
{
  uint64_t res = 0;
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

  // the edge always runs perpendicular to the direction we were checking in
  Point edgeDirection = edgeSide.rotate();
  // check that neither side of the edge changes (to accout for potential weird corners)
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

uint64_t Region::discountedPrice()
{
  uint64_t res = 0;
  // first key is the direction the edge is in from a plot
  // the second key is the node we're checking from
  // value is boolean for whether this edge is accounted for
  map<Point, map<Point, bool>> alreadyChecked{};

  for (auto plot : plots)
  {
    for (auto edgeSide : directions) { // check if there's an edge in any of the directions from the current plot
      if (
        !plots.contains(plot.first + edgeSide) &&
        // don't check the same edge twice
        !alreadyChecked[edgeSide][plot.first]
      )
      {
        auto edgePoints = runEdge(plot.first, edgeSide);
        // the edge goes in this direction
        auto edgeDir = edgeSide.rotate();
        auto edgeNode = edgePoints[0];
        // add the start and end of the edge to the list of checked things (the loop edge cases are wonky)
        alreadyChecked[edgeSide][edgeNode] = true;
        alreadyChecked[edgeSide][edgePoints[1]] = true;
        res++;

        // add all edge pieces to the checked list
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