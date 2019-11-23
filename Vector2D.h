#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
 public:
  double x, y;
  Vector2D();
  Vector2D(double in_x, double in_y);
};

Vector2D operator*(const Vector2D v1, const double d);
Vector2D operator/(const Vector2D v1, const double d);
std::ostream& operator<<(std::ostream& os, const Vector2D v1);
#endif