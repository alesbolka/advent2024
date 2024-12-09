#ifndef _H_POINT
#define _H_POINT

#include <stdexcept>
#include <iostream>

namespace helpers
{

namespace point
{

struct Point
{
  int y;
  int x;
  inline Point operator +(const Point& other)
  {
    Point res;
    res.y = y + other.y;
    res.x = x + other.x;
    return res;
  }
  inline Point operator +(const Point& other) const
  {
    Point res;
    res.y = y + other.y;
    res.x = x + other.x;
    return res;
  }

  inline Point operator -(const Point& other)
  {
    Point res;
    res.y = y - other.y;
    res.x = x - other.x;
    return res;
  }

  inline Point operator -(const Point& other) const
  {
    Point res;
    res.y = y - other.y;
    res.x = x - other.x;
    return res;
  }

  inline Point& operator +=(const Point& other)
  {
    this->y += other.y;
    this->x += other.x;
    return *this;
  }

  inline Point& operator -=(const Point& other)
  {
    this->y -= other.y;
    this->x -= other.x;
    return *this;
  }

  inline bool operator==(const Point& right)
  {
    return y == right.y && x == right.x;
  }

  inline bool operator <(const Point& other) const
  {
    if (y == other.y) {
      return x < other.x;
    }

    return y < other.y;
  }

  Point rotate();
};


inline std::ostream& operator << (std::ostream& outs, const Point& pt) {
  return outs << "(" << pt.y << "," << pt.x << ")";
}

const struct Point LEFT { 0, -1 };
const struct Point RIGHT { 0, 1 };
const struct Point UP { -1, 0 };
const struct Point DOWN { 1, 0 };

const struct Point UP_LEFT { -1, -1 };
const struct Point UP_RIGHT { -1, 1 };
const struct Point DOWN_LEFT { 1, -1 };
const struct Point DOWN_RIGHT { 1, 1 };

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

}
}

#endif