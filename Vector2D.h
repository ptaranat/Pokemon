#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D {
 public:
  double x, y;  // Displacement values of the vector.
  Vector2D();   // Default constructor initializes x, y to 0.0.
  Vector2D(double in_x, double in_y);  // Sets x and y to in_x and in_y.
};

Vector2D operator*(const Vector2D v1, const double d);
Vector2D operator/(const Vector2D v1, const double d);
std::ostream& operator<<(std::ostream& os, const Vector2D v1);
#endif