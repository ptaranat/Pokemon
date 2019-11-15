#include "Point2D.h"
#include <cmath>
// Constructor
Point2D::Point2D() {
    this->x = 0;
    this->y = 0;
}
// Constructor
Point2D::Point2D(double in_x, double in_y) {
    this->x = in_x;
    this->y = in_y;
}
// Returns Cartesian distance between two points
double GetDistanceBetween(const Point2D p1, const Point2D p2) {
    return sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2));
}
std::ostream& operator<<(std::ostream& os, const Point2D p1);
// TODO Implement Vector2D
/*
Point2D operator+(const Point2D p1, const Vector2D v1);
Vector2D operator-(const Point2D p1, const Point2D p2);
*/