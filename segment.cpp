#include "segment.hpp"
#include "vector.hpp"
#include "polygon.hpp"

Segment::Segment(const Point& set_a, const Point& set_b) : a(set_a), b(set_b) {}

template <> bool Segment::crosses(const Segment& s, bool count_touch) {
    return count_touch ?
        cross_prod(Vector(s.a, s.b), Vector(s.b, b)) * cross_prod(Vector(s.a, s.b), Vector(s.b, a)) <= 0 &&
        cross_prod(Vector(a, b), Vector(b, s.b)) * cross_prod(Vector(a, b), Vector(b, s.a)) <= 0 :
        cross_prod(Vector(s.a, s.b), Vector(s.b, b)) * cross_prod(Vector(s.a, s.b), Vector(s.b, a)) < 0 &&
        cross_prod(Vector(a, b), Vector(b, s.b)) * cross_prod(Vector(a, b), Vector(b, s.a)) < 0;
}

double Segment::len() {
    return Vector(a, b).len();
}

template <> bool Segment::crosses(const Polygon& p, bool count_touch) {
    if (count_touch) {
        for (auto i = p.begin(); i != p.end(); ++i) {
            if (crosses(*i, true)) {
                return true;
            }
        }
        return false;
    }

    int crossed_num = 0;
    for (auto i = p.begin(); i != p.end(); ++i) {
        if (crosses(*i, true)) {
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
    for (auto i = p.begin(); i != p.end(); ++i) {
        if (crosses(*i, false)) {
            return true;
        }
    }
    return false;
}

ostream& operator<< (ostream& out, const Segment& s) {
    out << "[ " << s.a << ", " << s.b << " ]";
    return out;
}