#ifndef POINT2D_H
#define POINT2D_H

#include <cmath>
#include <iostream>
#include "Vector2D.h"

class Point2D {
 public:
  double x, y;  // (x, y) values of the point.
  Point2D();    // Default constructor initializes x, y to 0.0.
  Point2D(double in_x, double in_y);  // Sets x and y to in_x and in_y.
};

double GetDistanceBetween(const Point2D p1, const Point2D p2);
std::ostream& operator<<(std::ostream& os, const Point2D p1);
Point2D operator+(const Point2D p1, const Vector2D v1);
Vector2D operator-(const Point2D p1, const Point2D p2);
#endif
