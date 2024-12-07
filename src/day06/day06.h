#ifndef DAY_06
#define DAY_06

#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace day06 {

struct Point
{
  int y;
  int x;
  Point operator +(const Point& other)
  {
    Point res;
    res.y = y + other.y;
    res.x = x + other.x;
    return res;
  }

  Point operator -(const Point& other)
  {
    Point res;
    res.y = y - other.y;
    res.x = x - other.x;
    return res;
  }

  Point& operator +=(const Point& other)
  {
    this->y += other.y;
    this->x += other.x;
    return *this;
  }

  Point& operator -=(const Point& other)
  {
    this->y -= other.y;
    this->x -= other.x;
    return *this;
  }

  bool operator==(const Point& right)
  {
    return y == right.y && x == right.x;
  }

  bool operator <(const Point& other) const
  {
    if (y == other.y) {
      return x < other.x;
    }

    return y < other.y;
  }

  Point rotate();
};

const struct Point LEFT { 0, -1 };
const struct Point RIGHT { 0, 1 };
const struct Point UP { -1, 0 };
const struct Point DOWN { 1, 0 };

inline Point Point::rotate()
{
  if (*this == LEFT)
  {
    return UP;
  }
  else if (*this == UP)
  {
    return RIGHT;
  }
  else if (*this == RIGHT)
  {
    return DOWN;
  }
  else if (*this == DOWN)
  {
    return LEFT;
  }

  throw std::invalid_argument("Invalid Point passed to the rotate function " + std::to_string(y) + "," + std::to_string(x));
}

inline std::ostream& operator << (std::ostream& outs, const Point& pt) {
  return outs << "(" << pt.y << "," << pt.x << ")";
}

class Map
{
public:
  Map(std::vector<std::string> input);
  std::vector<Point> findVisitedLocations(std::vector<Point>* blockers = nullptr);
protected:
  std::vector<std::vector<bool>> walls;
  Point start;
  Point direction;

  int64_t nodeId(Point node, Point* direction = nullptr);
  bool checkForRecursion(Point start, Point Direction);
  bool isWall(Point node);
  bool isOutOfBounds(Point node);
  void print(std::unordered_map<int64_t, bool> visited, Point direction, Point current, Point* tmpBlocker =
  nullptr);
  bool shouldCheckBlocker(std::unordered_map<int64_t, bool>* checked, Point node, Point direction);
};

inline int64_t task1(std::vector<std::string> input)
{
  Map map(input);
  return map.findVisitedLocations().size();
};
inline int64_t task2(std::vector<std::string> input)
{
  std::vector<Point> blockers{};
  Map map(input);
  map.findVisitedLocations(&blockers);

  return blockers.size();
};


int64_t task2_v2(std::vector<std::string> lines);
inline int64_t executor(int task, std::vector<std::string> input)
{

  if (task == 1) {
    return task1(input);
  }

  if (task == 2) {
    return task2_v2(input);
  }

  return -1;
};

}

#endif
