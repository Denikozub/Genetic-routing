#include "point.hpp"
#include <cmath>
using std::fabs;

Point::Point(double set_x, double set_y) : x(set_x), y(set_y) {}

bool operator== (const Point& p1, const Point& p2) {
    const double epsilon = 1e-7;
    return fabs(p1.x - p2.x) < epsilon && fabs(p1.y - p2.y) < epsilon;
}

bool operator!= (const Point& p1, const Point& p2) {
    return !operator==(p1, p2);
}