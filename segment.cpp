#include "segment.hpp"
#include "vector.hpp"

Segment::Segment(const Point& set_a, const Point& set_b) : a(set_a), b(set_b) {}

template <> bool Segment::crosses(const Segment& s) {
    return cross_prod(Vector(s.a, s.b), Vector(s.b, b)) * cross_prod(Vector(s.a, s.b), Vector(s.b, a)) < 0
        && cross_prod(Vector(a, b), Vector(b, s.b)) * cross_prod(Vector(a, b), Vector(b, s.a)) < 0;
}