#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include <iostream>

class Segment {
    Point a, b;
public:
    Segment(const Point&, const Point&);
    double len();
    template <typename T> bool crosses(const T&, bool=false);
    friend std::ostream& operator<< (std::ostream&, const Segment&);
};

#endif