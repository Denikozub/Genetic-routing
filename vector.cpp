#include "vector.hpp"
#include "point.hpp"
#include <cmath>
using std::sqrt;

Vector::Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
}

double Vector::len() {
    return sqrt(x * x + y * y);
}

double cross_prod(const Vector& v1, const Vector& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}