#pragma once

#include <ostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Point2D;

using PointPtr = std::unique_ptr<Point2D>;

class Point2D
{
private:
  int x, y;

public:
  Point2D(const int x, const int y)
    : x{x}, y{y} {}

  friend std::ostream& operator<<(std::ostream& os, const Point2D& p) // non-member function
  {
    return os << "(" << p.x << "," << p.y << ")";
  }

  bool operator<(const Point2D& p) const // member function
  {
    return pow(x,2) + pow(y,2) < pow(p.x,2) + pow(p.y,2);
  }

  static void sortPoints(std::vector<PointPtr>& points,bool reverse=false) // static member function
  {
    std::sort(points.begin(), points.end(), [=](const auto& a, const auto& b) { return reverse? !(*a < *b) : (*a < *b); });
  }
};


