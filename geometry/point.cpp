#include "point.hpp"
#include <cmath>


Point::Point(double set_x, double set_y) : x(set_x), y(set_y) {}


bool operator== (const Point& point1, const Point& point2) {
    const double epsilon = 1e-7;
    return std::fabs(point1.x - point2.x) < epsilon && std::fabs(point1.y - point2.y) < epsilon;
}


bool operator!= (const Point& point1, const Point& point2) {
    return !operator==(point1, point2);
}


std::ostream& operator<< (std::ostream& out, const Point& point) {
    out << "( " << point.x << ", " << point.y << " )";
    return out;
}