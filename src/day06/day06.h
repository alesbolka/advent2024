#ifndef DAY_06
#define DAY_06

#include <vector>
#include <string>
#include <unordered_map>

namespace day06 {

struct Point
{
  int y;
  int x;
};

inline std::ostream& operator << (std::ostream& outs, const Point& pt) {
  return outs << "(" << pt.y << "," << pt.x << ")";
}

inline bool operator==(const Point& left, const Point& right)
{
  return left.y == right.y && left.x == right.x;
}

const struct Point LEFT { 0, -1 };
const struct Point RIGHT { 0, 1 };
const struct Point UP { -1, 0 };
const struct Point DOWN { 1, 0 };

class Map
{
public:
  Map(std::vector<std::string> input);
  std::vector<Point> findVisitedLocations();
protected:
  std::vector<std::vector<bool>> walls;
  Point start;
  Point direction;

  void print(std::unordered_map<int, bool> visited, Point direction, Point current);
};

inline int64_t task1(std::vector<std::string> input)
{
  Map map(input);
  return map.findVisitedLocations().size();
};
inline int64_t task2(std::vector<std::string> input)
{
  Map map(input);
  return 0;
};

inline int64_t executor(int task, std::vector<std::string> input)
{

  if (task == 1) {
    return task1(input);
  }

  if (task == 2) {
    return task2(input);
  }

  return -1;
};

}

#endif
