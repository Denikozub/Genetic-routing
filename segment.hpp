#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"

class Segment {
    Point a, b;
public:
    Segment(const Point&, const Point&);
    template <typename T> bool crosses(const T&);
};

#endif