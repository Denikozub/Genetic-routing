#include "segment.hpp"
#include "vector.hpp"
#include "polygon.hpp"


Segment::Segment(const Point& set_a, const Point& set_b) : a(set_a), b(set_b) {}


template <> bool Segment::crosses(const Segment& segment, bool count_touch) {
    return count_touch ?
        cross_prod(Vector(segment.a, segment.b), Vector(segment.b, b)) * cross_prod(Vector(segment.a, segment.b), Vector(segment.b, a)) <= 0 &&
        cross_prod(Vector(a, b), Vector(b, segment.b)) * cross_prod(Vector(a, b), Vector(b, segment.a)) <= 0 :
        cross_prod(Vector(segment.a, segment.b), Vector(segment.b, b)) * cross_prod(Vector(segment.a, segment.b), Vector(segment.b, a)) < 0 &&
        cross_prod(Vector(a, b), Vector(b, segment.b)) * cross_prod(Vector(a, b), Vector(b, segment.a)) < 0;
}


double Segment::len() {
    return Vector(a, b).len();
}


template <> bool Segment::crosses(const Polygon& polygon, bool count_touch) {
    if (count_touch) {
        for (const auto& segment : polygon) {
            if (crosses(segment, true)) {
                return true;
            }
        }
        return false;
    }

    int crossed_num = 0;
    for (const auto& segment : polygon) {
        if (crosses(segment, true)) {
            ++crossed_num;
        }
    }
    if (crossed_num == 0) {
        return false;
    }
    if (crossed_num == 1 || crossed_num >= 4) {
        return true;
    }

    // 2 or 3 intersections - possible touch or overlap
    for (const auto& segment : polygon) {
        if (crosses(segment, false)) {
            return true;
        }
    }
    return false;
}


std::ostream& operator<< (std::ostream& out, const Segment& segment) {
    out << "[ " << segment.a << ", " << segment.b << " ]";
    return out;
}