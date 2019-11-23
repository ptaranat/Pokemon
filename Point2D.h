#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#include <iostream>
#include "Vector2D.h"

class Point2D {
 public:
  double x, y;
  Point2D();
  Point2D(double in_x, double in_y);
};

double GetDistanceBetween(const Point2D p1, const Point2D p2);
std::ostream& operator<<(std::ostream& os, const Point2D p1);
Point2D operator+(const Point2D p1, const Vector2D v1);
Vector2D operator-(const Point2D p1, const Point2D p2);
#endif
