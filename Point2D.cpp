#include "Point2D.h"

// Constructor
Point2D::Point2D() {
  x = 0.0;
  y = 0.0;
}
// Constructor
Point2D::Point2D(double in_x, double in_y) {
  x = in_x;
  y = in_y;
}
// Returns Cartesian distance between two points
double GetDistanceBetween(const Point2D p1, const Point2D p2) {
  return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}
std::ostream& operator<<(std::ostream& os, const Point2D p1) {
  os << '(' << p1.x << ", " << p1.y << ')';
  return os;
}

Point2D operator+(const Point2D p1, const Vector2D v1) {
  return Point2D(p1.x + v1.x, p1.y + v1.y);
}
Vector2D operator-(const Point2D p1, const Point2D p2) {
  return Vector2D(p1.x - p2.x, p1.y - p2.y);
}
bool operator==(const Point2D p1, const Point2D p2) {
  if (p1.x == p2.x && p1.y == p2.y) {
    return true;
  } else {
    return false;
  }
}
