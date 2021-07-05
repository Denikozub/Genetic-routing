#include "vector.hpp"
#include <cmath>
using std::sqrt;

Vector::Vector(const Point& a, const Point& b) {
    x = b.x - a.x;
    y = b.y - a.y;
}

double Vector::len() {
    return sqrt(x * x + y * y);
}

double cross_prod(const Vector& vector1, const Vector& vector2) {
    return vector1.x * vector2.y - vector1.y * vector2.x;
}