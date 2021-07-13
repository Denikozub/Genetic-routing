#include "segment.hpp"
#include "vector.hpp"
#include "polygon.hpp"


Segment::Segment(const Point& set_a, const Point& set_b) : a(set_a), b(set_b) {}


template <> bool Segment::crosses(const Segment& segment) {
    return cross_prod(Vector(segment.a, segment.b), Vector(segment.b, b)) * cross_prod(Vector(segment.a, segment.b), Vector(segment.b, a)) < 0 &&
        cross_prod(Vector(a, b), Vector(b, segment.b)) * cross_prod(Vector(a, b), Vector(b, segment.a)) < 0;
}


double Segment::len() {
    return Vector(a, b).len();
}


template <> bool Segment::crosses(const Polygon& polygon) {
    for (const auto& segment : polygon) {
        if (crosses(segment)) {
            return true;
        }
        if (*this == segment) {
            return false;
        }
    }
    return polygon.contains(a) && polygon.contains(b) ? true : false;
}


bool operator== (const Segment& segment1, const Segment& segment2) {
    return segment1.a == segment2.a && segment1.b == segment2.b;
}


std::ostream& operator<< (std::ostream& out, const Segment& segment) {
    out << "[ " << segment.a << ", " << segment.b << " ]";
    return out;
}