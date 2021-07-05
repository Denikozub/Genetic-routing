#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "point.hpp"
#include <iostream>
using std::ostream;

class Segment {
    Point a, b;
public:
    Segment(const Point&, const Point&);
    double len();
    template <typename T> bool crosses(const T&, bool=false);
    friend ostream& operator<< (ostream&, const Segment&);
};

#endif